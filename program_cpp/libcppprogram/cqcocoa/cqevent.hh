#pragma once

#include "cqcocoabase.hh"

_CQCOCOA_BEGIN_VERSION_NS

enum cqEventType {
    cqEventTypeTouches
};

cq_class(cqEvent, cqObject) {
    
    virtual cqEventType type();
};

_CQCOCOA_END_VERSION_NS
