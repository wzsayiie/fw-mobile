#include "csnode.hh"
#include "csgameobject.hh"

cq_member(csNode) {
};

void csNode::handleCreate () {}
void csNode::handleDestroy() {}

void csNode::dontDestroyOnLoad(csNodeRef node) {
    if (node == nullptr) {
        return;
    }
    
    if (node->isKindOfClass(csComponent::clazz())) {
        
        auto component = cqObject::cast<csComponent>(node);
        auto transform = component->getComponent<csTransform>();
        transform->asGlobalRoot();
        
    } else if (node->isKindOfClass(csGameObject::clazz())) {
        
        auto gameObject = cqObject::cast<csGameObject>(node);
        auto transform = gameObject->getComponent<csTransform>();
        transform->asGlobalRoot();
    }
}

void csNode::destroy(csNodeRef node) {
    if (node == nullptr) {
        return;
    }
    
    if (node->isKindOfClass(csComponent::clazz())) {
        
        auto component = cqObject::cast<csComponent>(node);
        auto gameObject = component->gameObject();
        gameObject->removeComponent(component);
        
    } else if (node->isKindOfClass(csGameObject::clazz())) {
        
        auto gameObject = cqObject::cast<csGameObject>(node);
        csGameObject::destroy(gameObject);
    }
}
