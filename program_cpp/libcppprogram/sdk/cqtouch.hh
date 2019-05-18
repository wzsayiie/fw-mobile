#pragma once

#include "cqcppbasis.hh"
#include "cqgeometry.hh"

cq_declare(cqView);
cq_declare(cqWindow);

cq_class(cqTouch, cqObject) {
    
    cqTouch();
    
    virtual void setLocationInWindow(cqWindowRef window, cqPoint location);
    virtual cqPoint locationInView(cqViewRef view);
};
