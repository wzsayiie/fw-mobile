#include "cqgameobject.hh"

cq_member(cqGameObject) {
};

cqGameObjectRef cqGameObject::createGameObject() {
    cqGameObjectRef object = cqGameObject::create();
    
    return object;
}

void cqGameObject::addComponent(cqComponentRef component) {
}
