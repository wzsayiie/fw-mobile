#include "csgameobject.hh"

cq_member(csGameObject) {
};

csGameObjectRef csGameObject::createGameObject() {
    csGameObjectRef object = csGameObject::create();
    
    return object;
}

void csGameObject::addComponent(csComponentRef component) {
}
