#include "csbaseobject.hh"
#include "csscenemanager.hh"

cq_member(csBaseObject) {
};

void csBaseObject::dontDestroyOnLoad(csBaseObjectRef object) {
    if (object == nullptr) {
        return;
    }
    
    if (object->isKindOfClass(csComponent::getClass())) {
        
        auto componentObject = cqObject::cast<csComponent>(object);
        auto gameObject = componentObject->gameObject();
        csSceneManager::destroy(gameObject);
        
    } else if (object->isKindOfClass(csGameObject::getClass())) {
        
        auto gameObject = cqObject::cast<csGameObject>(object);
        csSceneManager::destroy(gameObject);
    }
}

void csBaseObject::destroy(csBaseObjectRef object) {
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
        csSceneManager::destroy(gameObject);
    }
}
