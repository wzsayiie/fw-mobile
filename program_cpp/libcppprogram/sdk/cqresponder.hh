#pragma once

#include "cqevent.hh"

cq_class(cqResponder, cqObject) {
    
    cqResponder();
    
    virtual void touchesBegan(cqSet<cqTouch::ref>::ref touches, cqEvent::ref event);
    virtual void touchesMoved(cqSet<cqTouch::ref>::ref touches, cqEvent::ref event);
    virtual void touchesEnded(cqSet<cqTouch::ref>::ref touches, cqEvent::ref event);
};
