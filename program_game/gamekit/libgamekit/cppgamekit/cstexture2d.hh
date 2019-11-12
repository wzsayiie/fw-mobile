#pragma once

#include "cstexture.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csTexture2D, csTexture) {
    
    void init();
    void init(const std::vector<uint8_t> &data);
    void init(const std::string &path);
    
    virtual void *nativeTexture();
    
    int32_t width () override;
    int32_t height() override;
};

_CSGAMEKIT_END_VERSION_NS
