#pragma once

#include "cqgeometry.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_declare(cqView);
cq_declare(cqWindow);

cq_class(cqTouch, cqObject) {
    
    void init();
    void init(cqWindowRef window, cqPoint location);
    
    virtual cqPoint locationInView(cqViewRef view);
};

_CQAPPKIT_END_VERSION_NS
