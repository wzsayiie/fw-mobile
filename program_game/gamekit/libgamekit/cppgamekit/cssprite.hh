#pragma once

#include "cstexture2d.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csSprite, csNode) {
    
    void init();
    void init(csTexture2DRef texture);
    
    virtual csTexture2DRef texture();
};

_CSGAMEKIT_END_VERSION_NS
