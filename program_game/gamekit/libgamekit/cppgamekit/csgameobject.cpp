#include "csgameobject.hh"

//global data:

static std::set<csGameObjectRef> theGameObjects;

//game object:

cq_member(csGameObject) {
    std::string name;
    std::vector<csComponentRef> components;
};

//create and destroy:

void csGameObject::init() {
    init("");
}

void csGameObject::init(const std::string &name) {
    super::init();
    
    setName(name);
    handleCreate();
}

void csGameObject::destroy(csGameObjectRef gameObject) {
    if (gameObject != nullptr) {
        return;
    }

    for (csTransformRef transform : gameObject->transform()->children()) {
        destroy(transform->gameObject());
    }
    gameObject->handleDestroy();
}

void csGameObject::handleCreate() {
    //add:
    theGameObjects.insert(strongRef());
    //add default components:
    addComponent(csTransform::clazz());
}

void csGameObject::handleDestroy() {
    //destroy components:
    for (csComponentRef it : dat->components) {
        it->handleDestroy();
    }
    //remove:
    theGameObjects.erase(strongRef());
}

//properties:

void csGameObject::setName(const std::string &name) {
    dat->name = name;
}

std::string csGameObject::name() {
    return dat->name;
}

//components:

csComponentRef csGameObject::addComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return nullptr;
    }
    
    auto component = cqObject::cast<csComponent>(clazz->create()); {
        dat->components.push_back(component);
        component->setGameObjectIfNeeded(strongRef());
        component->handleCreate();
    }
    return component;
}

void csGameObject::removeComponent(csComponentRef component) {
    if (component == nullptr) {
        return;
    }
    if (cqVector::dontContain(dat->components, component)) {
        return;
    }
    
    component->handleDestroy();
    cqVector::erase(&dat->components, component);
}

std::vector<csComponentRef> csGameObject::getComponents(cqClass *clazz) {
    if (clazz == nullptr) {
        return std::vector<csComponentRef>();
    }
    
    std::vector<csComponentRef> vector;
    for (csComponentRef it : dat->components) {
        if (it->isKindOfClass(clazz)) {
            vector.push_back(it);
        }
    }
    return vector;
}

csComponentRef csGameObject::getComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return nullptr;
    }
    
    for (csComponentRef it : dat->components) {
        if (it->isKindOfClass(clazz)) {
            return it;
        }
    }
    return nullptr;
}

csTransformRef csGameObject::transform() {
    return getComponent<csTransform>();
}
