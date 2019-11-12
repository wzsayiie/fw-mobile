#include "csspriterenderder.hh"
#include "cqglkit.h"

cq_member(csSpriteRenderer) {
    csSpriteRef sprite;
    csVector2 size;
};

void csSpriteRenderer::handleRender() {
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
