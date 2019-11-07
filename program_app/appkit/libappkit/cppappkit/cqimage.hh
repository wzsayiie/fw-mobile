#pragma once

#include "cqappkitbase.hh"
#include "cqgeometry.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqImage, cqObject) {
    
    void init();
    void init(const std::vector<uint8_t> &data);
    void init(const std::string &file);
    
    ~cqImage();
    
    virtual void drawInRect(cqRect rect);
};

_CQAPPKIT_END_VERSION_NS
