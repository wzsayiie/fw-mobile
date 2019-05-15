#pragma once

#include "cqevent.hh"

cq_class(cqResponder, cqObject) {
    
    cqResponder();
    
    virtual void touchesBegan(const std::set<cqTouch::ref> &touches, cqEvent::ref event);
    virtual void touchesMoved(const std::set<cqTouch::ref> &touches, cqEvent::ref event);
    virtual void touchesEnded(const std::set<cqTouch::ref> &touches, cqEvent::ref event);
};
