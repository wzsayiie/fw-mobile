#pragma once

#include "cqevent.hh"

_CQUIKIT_BEGIN_VERSION_NS

cq_class(cqTouchesEvent, cqEvent) {
    
    cqEventType type() override;
};

_CQUIKIT_END_VERSION_NS
