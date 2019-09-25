#pragma once

#include "csbehaviour.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csCodeBehaviour, csBehaviour) {
    
    virtual bool external();
    virtual std::string externalName();
    
    virtual void emitUpdate();
    virtual void emitDestroy();
    
    //user-oriented lifecycle events:
    virtual void awake();
    virtual void start();
    virtual void update();
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
