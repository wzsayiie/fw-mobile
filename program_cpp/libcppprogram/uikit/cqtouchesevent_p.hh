#pragma once

#include "cqevent.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

cq_class(cqTouchesEvent, cqEvent) {
    
    cqTouchesEvent();
    
    cqEventType type() override;
};

_CQUIKIT_END_NS
