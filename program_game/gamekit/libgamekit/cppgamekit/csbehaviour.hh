#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csBehaviour, csComponent) {
    
    virtual void awake();
    
    virtual void start();
    
    virtual void update();
    
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
