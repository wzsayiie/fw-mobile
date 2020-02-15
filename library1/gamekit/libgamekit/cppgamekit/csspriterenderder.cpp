#include "csspriterenderder.hh"
#include "cqglkit.h"
#include "cstransform.hh"

cq_member(csSpriteRenderer) {
    csSpriteRef sprite;
    
    float width  = 0;
    float height = 0;
};

void csSpriteRenderer::handleRender(float offsetX, float offsetY) {
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
    float width  = dat->width ;
    float height = dat->height;
    if (cq_flt_equal(width, 0) || cq_flt_equal(height, 0)) {
        return;
    }
    
    //origin.
    auto transform = getComponent<csTransform>();
    float posX = transform->positionX();
    float posY = transform->positionY();
    float x = offsetX + posX - width  / 2;
    float y = offsetY + posY - height / 2;
    
    //draw.
    cq_draw_tex(x, y, width, height, (cq_tex *)texture->nativeTexture());
}

void csSpriteRenderer::setSprite(csSpriteRef sprite) {
    dat->sprite = sprite;
    
    if (cq_flt_equal(dat->width, 0) || cq_flt_equal(dat->height, 0)) {
        csTexture2DRef texture;
        if (sprite != nullptr) {
            texture = sprite->texture();
        }
        if (texture != nullptr) {
            dat->width  = texture->width () / cq_wnd_scale();
            dat->height = texture->height() / cq_wnd_scale();
        }
    }
}

csSpriteRef csSpriteRenderer::sprite() {
    return dat->sprite;
}

void csSpriteRenderer::setSize(float width, float height) {
    dat->width  = width ;
    dat->height = height;
}

float csSpriteRenderer::width () {return dat->width ;}
float csSpriteRenderer::height() {return dat->height;}
