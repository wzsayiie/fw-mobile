#pragma once

#include "cqcppbasis.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

enum cqEventType {
    cqEventTypeTouches
};

cq_class(cqEvent, cqObject) {
    
    cqEvent();
    
    virtual cqEventType type();
};

_CQUIKIT_END_NS
