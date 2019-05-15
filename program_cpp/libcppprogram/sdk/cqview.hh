#pragma once

#include "cqresponder.hh"
#include "cqgeometry.hh"

cq_class(cqView, cqResponder) {
    
    cqView();
    
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    virtual cqView::weak_ref superview();
    virtual const std::vector<cqView::ref> &subviews();
    virtual void addSubview(cqView::ref subview);
    virtual void removeFromSuperview();
    
    virtual cqView::ref hitTest(cqPoint point, cqEvent::ref event);
    virtual bool pointInside(cqPoint point, cqEvent::ref event);
};
