#pragma once

#include "csgeometry.hh"
#include "csrenderer.hh"
#include "cssprite.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csSpriteRenderer, csRenderer) {
    
    void handleRender(csVector2 offset) override;
    
    virtual void setSprite(csSpriteRef sprite);
    virtual csSpriteRef sprite();
    
    virtual void setSize(csVector2 size);
    virtual csVector2 size();
};

_CSGAMEKIT_END_VERSION_NS
