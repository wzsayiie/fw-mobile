#pragma once

#include "cqevent.hh"
#include "cqtouch.hh"

cq_class(cqResponder, cqObject) {
    
    cqResponder();
    
    virtual cqResponderRef nextResponder();
    
    virtual void touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event);
    virtual void touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event);
    virtual void touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event);
};
