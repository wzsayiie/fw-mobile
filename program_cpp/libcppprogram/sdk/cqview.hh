#pragma once

#include "cqresponder.hh"
#include "cqgeometry.hh"

cq_declare(cqViewController);

cq_class(cqView, cqResponder) {
    
    cqView();
    
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    virtual cqViewRef window();
    virtual cqViewRef superview();
    virtual const std::vector<cqViewRef> &subviews();
    virtual void addSubview(cqViewRef subview);
    virtual void removeFromSuperview();
    
    virtual cqPoint convertPointFromView(cqPoint point, cqViewRef view);
    virtual cqPoint convertPointToView(cqPoint point, cqViewRef view);
    
    virtual cqViewRef hitTest(cqPoint point, cqEventRef event);
    virtual bool pointInside(cqPoint point, cqEventRef event);
    
    virtual void setViewController(cqViewControllerRef viewController);
    virtual cqViewControllerRef viewController();
    
    cqResponderRef nextResponder() override;
};
