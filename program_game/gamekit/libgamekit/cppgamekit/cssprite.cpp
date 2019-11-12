#include "cssprite.hh"

cq_member(csSprite) {
    csTexture2DRef texture;
};

void csSprite::init() {
    super::init();
}

void csSprite::init(csTexture2DRef texture) {
    super::init();
    
    dat->texture = texture;
}

csTexture2DRef csSprite::texture() {
    return dat->texture;
}
