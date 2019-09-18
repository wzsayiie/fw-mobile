#pragma once

#include "csbehaviour.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csCodeBehaviour, csBehaviour) {
    
    virtual void awake    ();
    virtual void start    ();
    virtual void update   ();
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
