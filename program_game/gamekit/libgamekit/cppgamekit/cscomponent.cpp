#include "cscomponent.hh"
#include "csgameobject.hh"

cq_member(csComponent) {
    csGameObjectWeakRef gameObject;
};

void csComponent::setGameObject(csGameObjectRef gameObject) {
    dat->gameObject = gameObject;
}

csGameObjectRef csComponent::gameObject() {
    return dat->gameObject.lock();
}
