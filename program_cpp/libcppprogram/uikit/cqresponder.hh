#pragma once

#include "cqevent.hh"
#include "cqtouch.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

cq_class(cqResponder, cqObject) {
    
    virtual cqResponderRef nextResponder();
    
    virtual void touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event);
    virtual void touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event);
    virtual void touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event);
};

_CQUIKIT_END_NS
