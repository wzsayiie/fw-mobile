#include "csspriterenderder.hh"
#include "cqglkit.h"
#include "cstransform.hh"

cq_member(csSpriteRenderer) {
    csSpriteRef sprite;
    csVector2 size;
};

void csSpriteRenderer::handleRender(csVector2 offset) {
    //texture.
    csTexture2DRef texture; {
        if (dat->sprite != nullptr) {
            texture = dat->sprite->texture();
        }
    }
    if (texture == nullptr) {
        return;
    }
    
    //size.
    csVector2 size = dat->size;
    if (cq_flt_equal(size.x, 0) || cq_flt_equal(size.y, 0)) {
        return;
    }
    
    //origin.
    csVector2 pos = getComponent<csTransform>()->position();
    float x = offset.x + pos.x - size.x / 2;
    float y = offset.y + pos.y - size.y / 2;
    
    //draw.
    cq_draw_tex(x, y, size.x, size.y, (cq_tex *)texture->nativeTexture());
}

void csSpriteRenderer::setSprite(csSpriteRef sprite) {
    dat->sprite = sprite;
    
    if (cq_flt_equal(dat->size.x, 0) || cq_flt_equal(dat->size.y, 0)) {
        csTexture2DRef texture;
        if (sprite != nullptr) {
            texture = sprite->texture();
        }
        if (texture != nullptr) {
            dat->size.x = texture->width () / cq_wnd_scale();
            dat->size.y = texture->height() / cq_wnd_scale();
        }
    }
}

csSpriteRef csSpriteRenderer::sprite() {
    return dat->sprite;
}

void csSpriteRenderer::setSize(csVector2 size) {
    dat->size = size;
}

csVector2 csSpriteRenderer::size() {
    return dat->size;
}
