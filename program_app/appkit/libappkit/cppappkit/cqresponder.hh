#pragma once

#include "cqevent.hh"
#include "cqtouch.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqResponder, cqObject) {
    
    virtual cqResponderRef nextResponder();
    
    virtual void touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event);
    virtual void touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event);
    virtual void touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event);
};

_CQAPPKIT_END_VERSION_NS
