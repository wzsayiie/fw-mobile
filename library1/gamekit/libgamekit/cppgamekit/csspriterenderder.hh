#pragma once

#include "csrenderer.hh"
#include "cssprite.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csSpriteRenderer, csRenderer) {
    
    void handleRender(float offsetX, float offsetY) override;
    
    virtual void setSprite(csSpriteRef sprite);
    virtual csSpriteRef sprite();
    
    virtual void setSize(float width, float height);
    virtual float width();
    virtual float height();
};

_CSGAMEKIT_END_VERSION_NS
