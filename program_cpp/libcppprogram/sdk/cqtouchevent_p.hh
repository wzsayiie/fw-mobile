#pragma once

#include "cqevent.hh"

cq_class(cqTouchEvent, cqEvent) {
    
    cqTouchEvent();
    
    cqEventType type() override;
};
