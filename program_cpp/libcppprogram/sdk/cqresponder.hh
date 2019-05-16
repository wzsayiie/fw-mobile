#pragma once

#include "cqevent.hh"

cq_class(cqResponder, cqObject) {
    
    cqResponder();
    
    virtual cqResponder::Ref nextResponder();
    
    virtual void touchesBegan(const std::set<cqTouch::Ref> &touches, cqEvent::Ref event);
    virtual void touchesMoved(const std::set<cqTouch::Ref> &touches, cqEvent::Ref event);
    virtual void touchesEnded(const std::set<cqTouch::Ref> &touches, cqEvent::Ref event);
};
