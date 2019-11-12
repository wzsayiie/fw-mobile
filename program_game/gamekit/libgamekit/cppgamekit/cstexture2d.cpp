#include "cstexture2d.hh"
#include "cqglkit.h"

cq_member(csTexture2D) {
    cq_tex *tex = nullptr;
};

void csTexture2D::init() {
    super::init();
    
    dat->tex = nullptr;
}

void csTexture2D::init(const std::vector<uint8_t> &data) {
    super::init();
    
    dat->tex = cq_img_from_data(data.data(), (int32_t)data.size());
}

void csTexture2D::init(const std::string &path) {
    super::init();
    
    dat->tex = cq_img_from_file(path.c_str());
}

void *csTexture2D::nativeTexture() {
    return dat->tex;
}

int32_t csTexture2D::width() {
    return cq_tex_pw(dat->tex);
}

int32_t csTexture2D::height() {
    return cq_tex_ph(dat->tex);
}
