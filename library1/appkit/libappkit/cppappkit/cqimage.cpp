#include "cqimage.hh"
#include "cqglkit.h"

cq_member(cqImage) {
    cq_tex *tex = nullptr;
};

void cqImage::init() {
    super::init();
}

void cqImage::init(const std::vector<uint8_t> &data) {
    super::init();
    
    dat->tex = cq_img_from_data(data.data(), (int32_t)data.size());
}

void cqImage::init(const std::string &file) {
    super::init();
    
    dat->tex = cq_img_from_file(file.c_str());
}

cqImage::~cqImage() {
    cq_del_tex(dat->tex);
}

void cqImage::drawInRect(cqRect rect) {
    float x = rect.origin.x;
    float y = rect.origin.y;
    float w = rect.size.width;
    float h = rect.size.height;
    cq_draw_tex(x, y, w, h, dat->tex);
}
