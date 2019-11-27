#pragma once

#include "cqappkitbase.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqFont, cqObject) {
    
    static cqFontRef systemFontOfSize(float size);
    
    virtual void *nativeFont();
};

_CQAPPKIT_END_VERSION_NS
