#pragma once

#include "csnode.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csTexture, csNode) {
    
    //NOTE: this texture's pixel size.
    virtual int32_t width ();
    virtual int32_t height();
};

_CSGAMEKIT_END_VERSION_NS
