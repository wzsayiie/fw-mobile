#pragma once

#include "cqview.hh"

_CQAPPKIT_BEGIN_VERSION_NS

enum class cqControlState {
    Normal,
};

enum class cqControlEvent {
    TouchDown,
    TouchUpInside,
    TouchUpOutside,
};

cq_class(cqControl, cqView) {
    
    virtual cqControlState state();
    
    virtual void setActionForEvent(cqControlEvent event, std::function<void ()> action);
    virtual void removeActionForEvent(cqControlEvent event);
    virtual void sendEvent(cqControlEvent event);
};

_CQAPPKIT_END_VERSION_NS
