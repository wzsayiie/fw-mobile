#pragma once

#include "cqimage.hh"
#include "cqview.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqImageView, cqView) {
    
    void init();
    void init(cqRect frame);
    void init(cqImageRef image);
    
    virtual void setImage(cqImageRef image);
    virtual cqImageRef image();
    
    void drawRect(cqRect rect) override;
};

_CQAPPKIT_END_VERSION_NS
