#pragma once

#include "cqcomponent.hh"

_CQGAMEKIT_BEGIN_VERSION_NS

cq_class(cqGameObject, cqGKObject) {
    
    static cqGameObjectRef createGameObject();
    
    virtual void addComponent(cqComponentRef component);
};

_CQGAMEKIT_END_VERSION_NS
