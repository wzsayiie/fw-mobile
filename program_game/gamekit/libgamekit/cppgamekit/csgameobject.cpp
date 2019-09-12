#include "csgameobject.hh"
#include "csscenemanager.hh"

cq_member(csGameObject) {
    std::string name;
    
    csGameObjectWeakRef parent;
    std::vector<csGameObjectRef> children;
    
    std::map<cqClass *, csComponentRef> components;
};

csGameObjectRef csGameObject::createWithName(const std::string &name) {
    return csSceneManager::createGameObject(name);
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

void csGameObject::detachChildren() {
    for (auto &it : dat->children) {
        it->dat->parent.reset();
    }
    dat->children.clear();
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
    
    //component initialization.
    component->awake();
    component->start();
}

void csGameObject::removeComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return;
    }
    if (cqMap::dontContain(dat->components, clazz)) {
        return;
    }
    
    csComponentRef component = dat->components[clazz];
    component->onDestroy();
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

void csGameObject::update() {
    
    //NOTE: it's possibly to destroy component in update(),
    //keep the traversed container unchanged.
    std::map<cqClass *, csComponentRef> components = dat->components;
    for (auto &cp : components) {
        cp.second->update();
    }
}

void csGameObject::onDestroy() {
    for (auto &cp : dat->components) {
        cp.second->onDestroy();
    }
}

csGameObject::~csGameObject() {
    puts("~csGameObject");
}
