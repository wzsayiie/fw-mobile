#include "csgamekitarche.h"
#include "csgamekit.hh"

//obj:

struct RefItem {
    int32_t count = 0;
    cqObjectRef object;
};
static std::map<int64_t, RefItem> theRefPool;

template<class T, class F> typename cqRef<T>::Strong cs_get(F from) {
    int64_t index = *(int64_t *)&from;
    
    if (index == 0) {
        return typename cqRef<T>::Strong();
    }
    if (cqMap::dontContain(theRefPool, index)) {
        return typename cqRef<T>::Strong();
    }
    
    RefItem &item = theRefPool[index];
    if (!item.object->isKindOfClass(T::clazz())) {
        return typename cqRef<T>::Strong();
    }
    
    return cqObject::cast<T>(item.object);
}

template<class T> T cs_retain(cqObjectRef object) {
    T ret = {0};
    
    if (object == nullptr) {
        return ret;
    }
    
    auto index = (int64_t)object.get();
    if (index == 0) {
        return ret;
    }
    
    if (cqMap::dontContain(theRefPool, index)) {
        RefItem item; {
            item.count = 1;
            item.object = object;
        }
        theRefPool[index] = item;
    } else {
        RefItem &item = theRefPool[index];
        item.count += 1;
    }
    
    *(int64_t *)&ret = index;
    return ret;
}

void cs_retain(cs_obj obj) {
    if (obj.index == 0) {
        return;
    }
    if (cqMap::dontContain(theRefPool, obj.index)) {
        return;
    }
    
    RefItem &item = theRefPool[obj.index];
    item.count += 1;
}

void cs_release(cs_obj obj) {
    if (obj.index == 0) {
        return;
    }
    if (cqMap::dontContain(theRefPool, obj.index)) {
        return;
    }
    
    RefItem &item = theRefPool[obj.index];
    if (item.count > 1) {
        item.count -= 1;
    } else {
        theRefPool.erase(obj.index);
    }
}

//node:

void cs_dont_destroy_on_load(cs_node node) {
    csNodeRef nodeObject = cs_get<csNode>(node);
    csNode::dontDestroyOnLoad(nodeObject);
}

void cs_destroy(cs_node node) {
    csNodeRef nodeObject = cs_get<csNode>(node);
    csNode::destroy(nodeObject);
}

static csGameObjectRef cs_node_gobj(cs_node node) {
    csNodeRef nodeObject = cs_get<csNode>(node);
    if (nodeObject == nullptr) {
        return nullptr;
    }

    if (nodeObject->isKindOfClass(csComponent::clazz())) {
        
        auto componentObject = cqObject::cast<csComponent>(nodeObject);
        return componentObject->gameObject();
        
    } else if (nodeObject->isKindOfClass(csGameObject::clazz())) {
        
        return cqObject::cast<csGameObject>(nodeObject);
        
    } else {
        
        return nullptr;
    }
}

//scene:

cs_scene cs_create_scene(const char *name) {
    csSceneRef sceneObject = csSceneManager::createScene(cqString::make(name));
    return cs_retain<cs_scene>(sceneObject);
}

const char *cs_scene_name(cs_scene scene) {
    csSceneRef sceneObject = cs_get<csScene>(scene);
    
    if (sceneObject != nullptr) {
        std::string name = sceneObject->name();
        return cq_store_str(name.c_str());
    } else {
        return cq_store_str(nullptr);
    }
}

void cs_load_scene(const char *name) {
    csSceneManager::loadScene(cqString::make(name));
}

cs_scene cs_active_scene() {
    csSceneRef sceneObject = csSceneManager::activeScene();
    return cs_retain<cs_scene>(sceneObject);
}

//gobj:

cs_gobj cs_create_gobj(const char *name) {
    csGameObjectRef gameObject = csGameObject::createWithName(cqString::make(name));
    return cs_retain<cs_gobj>(gameObject);
}

void cs_set_gobj_name(cs_gobj gobj, const char *name) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    
    if (gameObject != nullptr) {
        gameObject->setName(cqString::make(name));
    }
}

const char *cs_gobj_name(cs_gobj gobj) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    
    if (gameObject != nullptr) {
        std::string name = gameObject->name();
        return cq_store_str(name.c_str());
    } else {
        return cq_store_str(nullptr);
    }
}

static std::vector<csGameObjectRef> theRootCache;

int32_t cs_list_root_begin(cs_scene scene) {
    theRootCache.clear();
    
    csSceneRef sceneObject = cs_get<csScene>(scene);
    if (sceneObject != nullptr) {
        theRootCache = sceneObject->rootGameObjects();
    }
    return (int32_t)theRootCache.size();
}

cs_gobj cs_list_root_at(int32_t index) {
    if (0 <= index && index < (int32_t)theRootCache.size()) {
        return cs_retain<cs_gobj>(theRootCache[index]);
    } else {
        return cs_retain<cs_gobj>(nullptr);
    }
}

void cs_list_root_end() {
    theRootCache.clear();
}

//comp:

cs_gobj cs_comp_gobj(cs_comp comp) {
    csComponentRef componentObject = cs_get<csComponent>(comp);
    
    csGameObjectRef gameObject = nullptr;
    if (componentObject != nullptr) {
        gameObject = componentObject->gameObject();
    }
    return cs_retain<cs_gobj>(gameObject);
}

cq_class(csExternalScript, csScript) {
    
    virtual void setExternalName(const std::string &name);
    std::string externalName() override;
    
    void awake    () override;
    void start    () override;
    void update   () override;
    void onDestroy() override;
};

cq_member(csExternalScript) {
    std::string externalName;
};

static cqClass *cs_cls_from_str(const std::string &str) {
    
    if (str == "anim"    ) { return csAnimation  ::clazz(); }
    if (str == "animator") { return csAnimator   ::clazz(); }
    if (str == "camera"  ) { return csCamera     ::clazz(); }
    if (str == "collider") { return csCollider   ::clazz(); }
    if (str == "mfilter" ) { return csMapFilter  ::clazz(); }
    if (str == "mrender" ) { return csMapRenderer::clazz(); }
    if (str == "rigid"   ) { return csRigidBody  ::clazz(); }
    if (str == "script"  ) { return csScript     ::clazz(); }
    if (str == "xform"   ) { return csTransform  ::clazz(); }
    
    //regard unknown name as external script.
    return csExternalScript::clazz();
}

cs_comp cs_add_comp(cs_gobj gobj, const char *cls) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    if (gameObject == nullptr || cqString::empty(cls)) {
        return cs_retain<cs_comp>(nullptr);
    }
    
    cqClass *clazz = cs_cls_from_str(cls);
    csComponentRef componentObject = gameObject->addComponent(clazz);
    
    if (componentObject->isKindOfClass(csExternalScript::clazz())) {
        auto scriptObject = cqObject::cast<csExternalScript>(componentObject);
        scriptObject->setExternalName(cls);
    }
    return cs_retain<cs_comp>(componentObject);
}

void cs_remove_comp(cs_gobj gobj, struct cs_comp comp) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    if (gameObject == nullptr) {
        return;
    }
    
    csComponentRef componentObject = cs_get<csComponent>(comp);
    if (componentObject == nullptr) {
        return;
    }
    
    gameObject->removeComponent(componentObject);
}

static std::vector<csComponentRef> theCompCache;

int32_t cs_list_comp_begin(cs_node node, const char *cls) {
    theCompCache.clear();
    
    csGameObjectRef gameObject = cs_node_gobj(node);
    if (gameObject == nullptr || cqString::empty(cls)) {
        return 0;
    }
    
    cqClass *clazz = cs_cls_from_str(cls);
    if (clazz->isKindOfClass(csExternalScript::clazz())) {
        
        auto candidates = gameObject->getComponents<csExternalScript>();
        for (csExternalScriptRef it : candidates) {
            if (it->externalName() == cls) {
                theCompCache.push_back(it);
            }
        }
        
    } else {
        
        theCompCache = gameObject->getComponents(clazz);
    }
    
    return (int32_t)theCompCache.size();
}

cs_comp cs_list_comp_at(int32_t index) {
    if (0 <= index && index < (int32_t)theCompCache.size()) {
        return cs_retain<cs_comp>(theCompCache[index]);
    } else {
        return cs_retain<cs_comp>(nullptr);
    }
}

void cs_list_comp_end() {
    theCompCache.clear();
}

cs_comp cs_get_comp(cs_node node, const char *cls) {
    csGameObjectRef gameObject = cs_node_gobj(node);
    if (gameObject == nullptr || cqString::empty(cls)) {
        return cs_retain<cs_comp>(nullptr);
    }
    
    cqClass *clazz = cs_cls_from_str(cls);
    if (clazz->isKindOfClass(csExternalScript::clazz())) {
        
        auto candidates = gameObject->getComponents<csExternalScript>();
        for (csExternalScriptRef it : candidates) {
            if (it->externalName() == cls) {
                return cs_retain<cs_comp>(it);
            }
        }
        return cs_retain<cs_comp>(nullptr);
        
    } else {
        
        auto componentObject = gameObject->getComponent(clazz);
        return cs_retain<cs_comp>(componentObject);
    }
}

//script:

static cs_script_callback_t theScriptCallback = nullptr;

void cs_set_script_callback(cs_script_callback_t callback) {
    theScriptCallback = callback;
}

void csExternalScript::setExternalName(const std::string &name) {
    dat->externalName = name;
}

std::string csExternalScript::externalName() {
    return dat->externalName;
}

static void emit_event(const char *event, csExternalScript *scriptObject) {
    if (theScriptCallback != nullptr) {
        cs_script script = {(int64_t)scriptObject};
        theScriptCallback(event, script);
    }
}

void csExternalScript::awake    () { emit_event("awake"     , this); }
void csExternalScript::start    () { emit_event("start"     , this); }
void csExternalScript::update   () { emit_event("update"    , this); }
void csExternalScript::onDestroy() { emit_event("on_destroy", this); }

//xform:

cs_xform cs_get_xform(cs_node node) {
    csGameObjectRef gameObject = cs_node_gobj(node);
    
    if (gameObject != nullptr) {
        return cs_retain<cs_xform>(gameObject->transform());
    }
    return cs_retain<cs_xform>(nullptr);
}

void cs_set_xform_pos(cs_xform xform, float x, float y, float z) {
    csTransformRef transformObject = cs_get<csTransform>(xform);
    
    if (transformObject != nullptr) {
        transformObject->setPosition(csVector3(x, y, z));
    }
}

static csVector3 cs_xform_pos(cs_xform xform) {
    csTransformRef transformObject = cs_get<csTransform>(xform);
    
    if (transformObject != nullptr) {
        return transformObject->position();
    }
    return csVector3();
}

float cs_xform_x(cs_xform xform) { return cs_xform_pos(xform).x; }
float cs_xform_y(cs_xform xform) { return cs_xform_pos(xform).y; }
float cs_xform_z(cs_xform xform) { return cs_xform_pos(xform).z; }

void cs_set_xform_parent(cs_xform xform, cs_xform parent) {
    csTransformRef transformObject = cs_get<csTransform>(xform);
    csTransformRef parentObject = cs_get<csTransform>(parent);
    
    if (transformObject != nullptr) {
        transformObject->setParent(parentObject);
    }
}

cs_xform cs_xform_parent(cs_xform xform) {
    csTransformRef transformObject = cs_get<csTransform>(xform);
    
    csTransformRef parentObject = nullptr;
    if (transformObject != nullptr) {
        parentObject = transformObject->parent();
    }
    return cs_retain<cs_xform>(parentObject);
}

static std::vector<csTransformRef> theChildCache;

int32_t cs_list_child_begin(struct cs_xform xform) {
    theChildCache.clear();
    
    csTransformRef transformObject = cs_get<csTransform>(xform);
    if (transformObject != nullptr) {
        theChildCache = transformObject->children();
    }
    return (int32_t)theChildCache.size();
}

struct cs_xform cs_list_child_at(int32_t index) {
    if (0 <= index && index < (int32_t)theChildCache.size()) {
        return cs_retain<cs_xform>(theChildCache[index]);
    } else {
        return cs_retain<cs_xform>(nullptr);
    }
}

void cs_list_child_end() {
    theChildCache.clear();
}

void cs_detach_children(struct cs_xform xform) {
    csTransformRef transformObject = cs_get<csTransform>(xform);
    
    if (transformObject != nullptr) {
        transformObject->detachChildren();
    }
}
