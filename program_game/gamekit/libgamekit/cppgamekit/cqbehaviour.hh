#pragma once

#include "cqcomponent.hh"

_CQGAMEKIT_BEGIN_VERSION_NS

cq_class(cqBehaviour, cqComponent) {
    
    virtual void awake();
    
    virtual void start();
    
    virtual void update();
};

_CQGAMEKIT_END_VERSION_NS
