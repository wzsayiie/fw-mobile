#pragma once

#include "cqevent.hh"

_CQCOCOA_BEGIN_VERSION_NS

cq_class(cqTouchesEvent, cqEvent) {
    
    cqEventType type() override;
};

_CQCOCOA_END_VERSION_NS
