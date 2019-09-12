#include "cscomponent.hh"
#include "csgameobject.hh"

cq_member(csComponent) {
    csGameObjectWeakRef gameObject;
};

void csComponent::resetGameObjectIfNeeded(csGameObjectRef gameObject) {
    if (dat->gameObject.lock() == nullptr) {
        dat->gameObject = gameObject;
    }
}

csGameObjectRef csComponent::gameObject() {
    return dat->gameObject.lock();
}

csComponentRef csComponent::getComponent(cqClass *clazz) {
    csGameObjectRef object = gameObject();
    
    if (object != nullptr) {
        return object->getComponent(clazz);
    } else {
        return nullptr;
    }
}

csTransformRef csComponent::transform() {
    return getComponent<csTransform>();
}

void csComponent::awake() {
}

void csComponent::start() {
}

void csComponent::update() {
}

void csComponent::onDestroy() {
}
