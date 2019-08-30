#pragma once

#include "cqgeometry.hh"

_CQCOCOA_BEGIN_VERSION_NS

cq_declare(cqView);
cq_declare(cqWindow);

cq_class(cqTouch, cqObject) {
    
    static cqTouchRef createWithLocation(cqWindowRef window, cqPoint location);
    
    virtual cqPoint locationInView(cqViewRef view);
};

_CQCOCOA_END_VERSION_NS
