#pragma once

#include "cqcolor.hh"
#include "cqgeometry.hh"
#include "cqresponder.hh"

_CQCOCOA_BEGIN_VERSION_NS

cq_declare(cqViewController);
cq_declare(cqWindow);

cq_class(cqView, cqResponder) {
    
    static cqViewRef createWithFrame(cqRect frame);
    
    //position:
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    //draw:
    virtual void setBackgroundColor(cqColor backgroundColor);
    virtual cqColor backgroundColor();
    
    virtual void drawSelfAndSubviews();
    virtual void drawBackgroundInRect(cqRect rect);
    virtual void drawInRect(cqRect rect);
    
    //superview and subviews:
    virtual cqWindowRef window();
    virtual cqViewRef superview();
    virtual const std::vector<cqViewRef> &subviews();
    virtual void addSubview(cqViewRef subview);
    virtual void removeFromSuperview();
    
    virtual void setViewController(cqViewControllerRef viewController);
    virtual cqViewControllerRef viewController();
    
    cqResponderRef nextResponder() override;
    
    //hit test:
    virtual cqPoint convertPointFromView(cqPoint point, cqViewRef view);
    virtual cqPoint convertPointToView(cqPoint point, cqViewRef view);
    
    virtual cqViewRef hitTest(cqPoint point, cqEventRef event);
    virtual bool pointInside(cqPoint point, cqEventRef event);
};

_CQCOCOA_END_VERSION_NS
