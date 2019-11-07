#include "cqimageview.hh"

cq_member(cqImageView) {
    cqImageRef image;
};

void cqImageView::init() {
    super::init();
}

void cqImageView::init(cqRect frame) {
    super::init(frame);
}

void cqImageView::init(cqImageRef image) {
    super::init();
    
    setImage(image);
}

void cqImageView::setImage(cqImageRef image) {
    dat->image = image;
}

cqImageRef cqImageView::image() {
    return dat->image;
}

void cqImageView::drawRect(cqRect rect) {
    if (dat->image != nullptr) {
        dat->image->drawInRect(rect);
    }
}
