#pragma once

#include "cqcppbasis.hh"
#include "cqgeometry.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

cq_declare(cqView);
cq_declare(cqWindow);

cq_class(cqTouch, cqObject) {
    
    static cqTouchRef createWithLocation(cqWindowRef window, cqPoint location);
    
    virtual cqPoint locationInView(cqViewRef view);
};

_CQUIKIT_END_NS
