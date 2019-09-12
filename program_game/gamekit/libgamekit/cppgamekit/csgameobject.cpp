#include "csgameobject.hh"
#include "csscenemanager.hh"

cq_member(csGameObject) {
    std::string name;
    
    csGameObjectWeakRef parent;
    std::vector<csGameObjectRef> children;
    
    std::map<cqClass *, csComponentRef> components;
};

csGameObjectRef csGameObject::createWithName(const std::string &name) {
    csGameObjectRef object = csGameObject::create();
    
    object->setName(name);
    //NOTE: transform component is default.
    object->addComponent(csTransform::getClass());
    //NOTE: attach to active scene.
    object->setParent(csSceneManager::activeSceneVirtualRoot());
    
    return object;
}

//properties:

void csGameObject::setName(const std::string &name) {
    dat->name = name;
}

std::string csGameObject::name() {
    return dat->name;
}

//hierarchy:

void csGameObject::setParent(csGameObjectRef parent) {
    csGameObjectRef oldParent = dat->parent.lock();
    
    if (oldParent == parent) {
        return;
    }
    
    //remove from old parent.
    if (oldParent != nullptr) {
        auto brothers = oldParent->dat->children;
        std::remove_if(brothers.begin(), brothers.end(), [=](csGameObjectRef it) {
            return it.get() == this;
        });
        dat->parent.reset();
    }
    
    //add to new parent.
    if (parent != nullptr) {
        parent->dat->children.push_back(strongRef());
        dat->parent = parent;
    }
}

csGameObjectRef csGameObject::parent() {
    return dat->parent.lock();
}

const std::vector<csGameObjectRef> &csGameObject::children() {
    return dat->children;
}

//components:

void csGameObject::addComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return;
    }
    if (cqMap::contains(dat->components, clazz)) {
        return;
    }
    
    csComponentRef component = cqObject::cast<csComponent>(clazz->create());
    component->resetGameObjectIfNeeded(strongRef());
    dat->components[clazz] = component;
}

void csGameObject::removeComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return;
    }
    
    dat->components.erase(clazz);
}

csComponentRef csGameObject::getComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return nullptr;
    }
    
    if (cqMap::contains(dat->components, clazz)) {
        return dat->components[clazz];
    } else {
        return nullptr;
    }
}

csTransformRef csGameObject::transform() {
    return getComponent<csTransform>();
}
