#include "cscomponent.hh"
#include "csgameobject.hh"

cq_member(csComponent) {
    csGameObjectWeakRef gameObject;
};

//properties:

void csComponent::setGameObjectIfNeeded(csGameObjectRef gameObject) {
    if (dat->gameObject.lock() == nullptr) {
        dat->gameObject = gameObject;
    }
}

csGameObjectRef csComponent::gameObject() {
    return dat->gameObject.lock();
}

//brother components:

std::vector<csComponentRef> csComponent::listComponents(cqClass *clazz) {
    csGameObjectRef object = gameObject();
    
    if (object != nullptr) {
        return object->listComponents(clazz);
    }
    return std::vector<csComponentRef>();
}

csComponentRef csComponent::getComponent(cqClass *clazz) {
    csGameObjectRef object = gameObject();
    
    if (object != nullptr) {
        return object->getComponent(clazz);
    }
    return nullptr;
}

csTransformRef csComponent::transform() {
    return getComponent<csTransform>();
}
