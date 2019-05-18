#pragma once

#include "cqcppbasis.hh"
#include "cqgeometry.hh"

cq_declare(cqView);
cq_declare(cqWindow);

cq_class(cqTouch, cqObject) {
    
    static cqTouchRef createWithLocation(cqWindowRef window, cqPoint location);
    
    cqTouch();
    
    virtual cqPoint locationInView(cqViewRef view);
};
