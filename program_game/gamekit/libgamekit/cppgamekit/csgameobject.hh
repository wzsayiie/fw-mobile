#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGameObject, csBaseObject) {
    
    static csGameObjectRef createGameObject();
    
    virtual void addComponent(csComponentRef component);
};

_CSGAMEKIT_END_VERSION_NS
