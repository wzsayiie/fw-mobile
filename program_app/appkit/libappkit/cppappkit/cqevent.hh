#pragma once

#include "cqappkitbase.hh"

_CQAPPKIT_BEGIN_VERSION_NS

enum cqEventType {
    cqEventTypeTouches
};

cq_class(cqEvent, cqObject) {
    
    virtual cqEventType type();
};

_CQAPPKIT_END_VERSION_NS
