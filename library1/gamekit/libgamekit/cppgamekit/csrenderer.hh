#pragma once

#include "cstransform.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csRenderer, csComponent) {
    
    static void renderAll(const std::vector<csTransformRef> &roots);
    
    virtual void handleRender(csVector2 offset);
};

_CSGAMEKIT_END_VERSION_NS
