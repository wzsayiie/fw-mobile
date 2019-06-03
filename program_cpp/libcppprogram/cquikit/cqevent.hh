#pragma once

#include "cqcppbasis.hh"

enum cqEventType {
    cqEventTypeTouches
};

cq_class(cqEvent, cqObject) {
    
    cqEvent();
    
    virtual cqEventType type();
};
