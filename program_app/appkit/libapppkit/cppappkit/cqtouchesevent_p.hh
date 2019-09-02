#pragma once

#include "cqevent.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqTouchesEvent, cqEvent) {
    
    cqEventType type() override;
};

_CQAPPKIT_END_VERSION_NS
