#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csVector2 {
    float x = 0;
    float y = 0;
};

cq_class(csTransform, csComponent) {
    
    virtual void setPosition(csVector2 position);
    virtual csVector2 position();
    
    virtual void setParent(csTransformRef parent);
    virtual csTransformRef parent();
};

_CSGAMEKIT_END_VERSION_NS
