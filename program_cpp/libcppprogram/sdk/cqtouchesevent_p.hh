#pragma once

#include "cqevent.hh"

cq_class(cqTouchesEvent, cqEvent) {
    
    cqTouchesEvent();
    
    cqEventType type() override;
};
