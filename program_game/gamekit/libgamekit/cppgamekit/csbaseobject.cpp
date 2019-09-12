#include "csbaseobject.hh"
#include "csscenemanager.hh"

cq_member(csBaseObject) {
};

void csBaseObject::dontDetachOnLoad(csBaseObjectRef object) {
    if (object == nullptr) {
        return;
    }
    
    csGameObjectRef gameObject;
    
    if (object->isKindOfClass(csComponent::getClass())) {
        auto componentObject = cqObject::cast<csComponent>(object);
        gameObject = componentObject->gameObject();
    } else if (object->isKindOfClass(csGameObject::getClass())) {
        gameObject = cqObject::cast<csGameObject>(object);
    }
    
    if (gameObject != nullptr) {
        gameObject->setParent(csSceneManager::globalVirtualRoot());
    }
}

void csBaseObject::detach(csBaseObjectRef object) {
    if (object == nullptr) {
        return;
    }
    
    if (object->isKindOfClass(csComponent::getClass())) {
        
        auto componentObject = cqObject::cast<csComponent>(object);
        auto gameObject = componentObject->gameObject();
        if (gameObject != nullptr) {
            gameObject->removeComponent(object->clazz());
        }
        
    } else if (object->isKindOfClass(csGameObject::getClass())) {
        
        auto gameObject = cqObject::cast<csGameObject>(object);
        gameObject->setParent(nullptr);
    }
}
