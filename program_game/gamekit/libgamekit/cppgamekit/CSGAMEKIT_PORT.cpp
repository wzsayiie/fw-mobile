#include "csgamekitarche.h"
#include "csgamekit.hh"

//obj:

struct ReferenceItem {
    int32_t referenceCount = 0;
    cqObjectRef object;
};
static std::map<int64_t, ReferenceItem> sReferencePool;

template<class T, class F> typename cqRef<T>::Strong cs_get(F from) {
    int64_t index = *(int64_t *)&from;
    
    if (index == 0) {
        return typename cqRef<T>::Strong();
    }
    if (cqMap::dontContain(sReferencePool, index)) {
        return typename cqRef<T>::Strong();
    }
    
    ReferenceItem &item = sReferencePool[index];
    if (!item.object->isKindOfClass(T::clazz())) {
        return typename cqRef<T>::Strong();
    }
    
    return cqObject::cast<T>(item.object);
}

template<class T> T cs_retain(cqObjectRef object) {
    int64_t index = 0;
    do {
        if (object == nullptr) {
            break;
        }
    
        index = (int64_t)object.get();
        if (index == 0) {
            break;
        }
    
        if (cqMap::dontContain(sReferencePool, index)) {
            ReferenceItem item; {
                item.referenceCount = 1;
                item.object = object;
            }
            sReferencePool[index] = item;
        } else {
            ReferenceItem &item = sReferencePool[index];
            item.referenceCount += 1;
        }
    } while (0);
    
    T ret = {index};
    return ret;
}

void cs_retain(cs_obj obj) {
    if (obj.index == 0) {
        return;
    }
    if (cqMap::dontContain(sReferencePool, obj.index)) {
        return;
    }
    
    ReferenceItem &item = sReferencePool[obj.index];
    item.referenceCount += 1;
}

void cs_release(cs_obj obj) {
    if (obj.index == 0) {
        return;
    }
    if (cqMap::dontContain(sReferencePool, obj.index)) {
        return;
    }
    
    ReferenceItem &item = sReferencePool[obj.index];
    if (item.referenceCount > 1) {
        item.referenceCount -= 1;
    } else {
        sReferencePool.erase(obj.index);
    }
}

//gk_obj:

void cs_dont_destroy_on_load(cs_gk_obj gk_obj) {
    csGKObjectRef object = cs_get<csGKObject>(gk_obj);
    csGKObject::dontDestroyOnLoad(object);
}

void cs_destroy(cs_gk_obj gk_obj) {
    csGKObjectRef object = cs_get<csGKObject>(gk_obj);
    csGKObject::destroy(object);
}

//scene:

cs_scene cs_create_scene(const char *name) {
    csSceneRef scene = csSceneManager::createScene(cqString::make(name));
    return cs_retain<cs_scene>(scene);
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

cs_scene cs_active_scene(void) {
    csSceneRef scene = csSceneManager::activeScene();
    return cs_retain<cs_scene>(scene);
}

//gobj:

cs_gobj cs_create_gobj(const char *name) {
    csGameObjectRef gameOject = csGameObject::createWithName(cqString::make(name));
    return cs_retain<cs_gobj>(gameOject);
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

void cs_set_gobj_parent(cs_gobj gobj, cs_gobj parent) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    csGameObjectRef parentObject = cs_get<csGameObject>(parent);
    
    if (gameObject != nullptr) {
        gameObject->setParent(parentObject);
    }
}

cs_gobj cs_gobj_parent(cs_gobj gobj) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    csGameObjectRef parentObject = nullptr;
    
    if (gameObject != nullptr) {
        parentObject = gameObject->parent();
    }
    return cs_retain<cs_gobj>(parentObject);
}

int32_t cs_child_num(cs_gobj gobj) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    
    if (gameObject != nullptr) {
        return (int32_t)gameObject->children().size();
    }
    return 0;
}

cs_gobj cs_child_at(cs_gobj gobj, int32_t index) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    csGameObjectRef childObject = nullptr;
    
    if (gameObject != nullptr) {
        const auto &children = gameObject->children();
        if (0 <= index && index < (int32_t)children.size()) {
            childObject = children[index];
        }
    }
    return cs_retain<cs_gobj>(childObject);
}

void cs_detach_children(cs_gobj gobj) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    
    if (gameObject != nullptr) {
        gameObject->detachChildren();
    }
}

int32_t cs_root_gobj_num(cs_scene scene) {
    csSceneRef sceneObject = cs_get<csScene>(scene);
    
    if (sceneObject != nullptr) {
        return (int32_t)sceneObject->rootGameObjects().size();
    }
    return 0;
}

cs_gobj cs_root_gobj_at(cs_scene scene, int32_t index) {
    csSceneRef sceneObject = cs_get<csScene>(scene);
    csGameObjectRef gameObject = nullptr;
    
    if (sceneObject != nullptr) {
        const auto &objects = sceneObject->rootGameObjects();
        if (0 <= index && index < (int32_t)objects.size()) {
            auto iter = objects.begin();
            std::advance(iter, index);
            gameObject = iter->second;
        }
    }
    return cs_retain<cs_gobj>(gameObject);
}

//comp:

cq_class(csExternalCode, csCodeBehaviour) {
    
    void awake    () override;
    void start    () override;
    void update   () override;
    void onDestroy() override;
};

cq_member(csExternalCode) {
};

static cqClass *classFromComponentID(cs_comp_id cid) {
    switch (cid) {
        case cs_cid_camera  : return csCamera::clazz();
        case cs_cid_code_beh: return csExternalCode::clazz();
        case cs_cid_xform   : return csTransform::clazz();
        default/* err cid */: return nullptr;
    }
}

cs_comp cs_add_comp(cs_gobj gobj, cs_comp_id cid) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    cqClass *clazz = classFromComponentID(cid);
    
    csComponentRef component = nullptr;
    if (gameObject != nullptr && clazz != nullptr) {
        component = gameObject->addComponent(clazz);
    }
    return cs_retain<cs_comp>(component);
}

void cs_remove_comp(cs_gobj gobj, cs_comp_id cid) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    cqClass *clazz = classFromComponentID(cid);
    
    if (gameObject != nullptr && clazz != nullptr) {
        gameObject->removeComponent(clazz);
    }
}

cs_comp cs_gobj_comp(cs_gobj gobj, cs_comp_id cid) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    cqClass *clazz = classFromComponentID(cid);
    
    csComponentRef component = nullptr;
    if (gameObject != nullptr && clazz != nullptr) {
        component = gameObject->getComponent(clazz);
    }
    return cs_retain<cs_comp>(component);
}

cs_gobj cs_comp_gobj(cs_comp comp) {
    csComponentRef component = cs_get<csComponent>(comp);
    
    csGameObjectRef gameObject = nullptr;
    if (component != nullptr) {
        gameObject = component->gameObject();
    }
    return cs_retain<cs_gobj>(gameObject);
}

cs_comp cs_comp_brother(cs_comp comp, cs_comp_id cid) {
    csComponentRef component = cs_get<csComponent>(comp);
    cqClass *clazz = classFromComponentID(cid);
    
    csComponentRef brother = nullptr;
    if (component != nullptr && clazz != nullptr) {
        brother = component->getComponent(clazz);
    }
    return cs_retain<cs_comp>(brother);
}

//code_beh:

static cs_cb_callback _cb_callback = nullptr;

static void emit_event(const char *event, csExternalCode *object) {
    if (_cb_callback != nullptr) {
        cs_code_beh beh = {(int64_t)object};
        _cb_callback(event, beh);
    }
}

void csExternalCode::awake    () { emit_event("awake"     , this); }
void csExternalCode::start    () { emit_event("start"     , this); }
void csExternalCode::update   () { emit_event("update"    , this); }
void csExternalCode::onDestroy() { emit_event("on_destroy", this); }

void cs_set_cb_callback(cs_cb_callback callback) {
    _cb_callback = callback;
}

//xform:

cs_xform cs_gobj_xform(cs_gobj gobj) {
    csGameObjectRef gameObject = cs_get<csGameObject>(gobj);
    
    csTransformRef transform = nullptr;
    if (gameObject != nullptr) {
        transform = gameObject->transform();
    }
    return cs_retain<cs_xform>(transform);
}

cs_xform cs_comp_xform(cs_comp comp) {
    csComponentRef component = cs_get<csComponent>(comp);
    
    csTransformRef transform = nullptr;
    if (component != nullptr) {
        transform = component->transform();
    }
    return cs_retain<cs_xform>(transform);
}

void cs_set_xform_xy(cs_xform xform, float x, float y) {
    csTransformRef transform = cs_get<csTransform>(xform);
    
    if (transform != nullptr) {
        transform->setPosition(csVector2(x, y));
    }
}

float cs_xform_x(cs_xform xform) {
    csTransformRef transform = cs_get<csTransform>(xform);
    
    if (transform != nullptr) {
        return transform->position().x;
    }
    return 0.F;
}

float cs_xform_y(cs_xform xform) {
    csTransformRef transform = cs_get<csTransform>(xform);
    
    if (transform != nullptr) {
        return transform->position().y;
    }
    return 0.F;
}

void cs_set_xform_parent(cs_xform xform, cs_xform parent) {
    csTransformRef transformObject = cs_get<csTransform>(xform);
    csTransformRef parentObject = cs_get<csTransform>(parent);
    
    if (transformObject != nullptr) {
        transformObject->setParent(parentObject);
    }
}

cs_xform cs_xform_parent(cs_xform xform) {
    csTransformRef transform = cs_get<csTransform>(xform);
    
    csTransformRef parent = nullptr;
    if (transform != nullptr) {
        parent = transform->parent();
    }
    return cs_retain<cs_xform>(parent);
}
