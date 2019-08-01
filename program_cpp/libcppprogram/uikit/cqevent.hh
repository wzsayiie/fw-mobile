#pragma once

#include "cquikitbase.hh"

_CQUIKIT_BEGIN_VERSION_NS

enum cqEventType {
    cqEventTypeTouches
};

cq_class(cqEvent, cqObject) {
    
    virtual cqEventType type();
};

_CQUIKIT_END_VERSION_NS
