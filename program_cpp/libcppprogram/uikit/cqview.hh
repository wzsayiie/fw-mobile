#pragma once

#include "cqresponder.hh"
#include "cqgeometry.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

cq_declare(cqViewController);
cq_declare(cqWindow);

cq_class(cqView, cqResponder) {
    
    static cqViewRef createWithFrame(cqRect frame);
    
    cqView();
    
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    virtual cqWindowRef window();
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

_CQUIKIT_END_NS
