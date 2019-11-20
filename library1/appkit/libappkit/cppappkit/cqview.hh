#pragma once

#include "cqlayer.hh"
#include "cqresponder.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_declare(cqViewController);
cq_declare(cqWindow);

cq_class(cqView, cqResponder) {
    
    void init();
    void init(cqRect frame);
    
    //position:
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    virtual void setCenter(cqPoint point);
    virtual cqPoint center();
    
    //draw:
    virtual cqLayerRef layer();
    
    virtual void setBackgroundColor(cqColor backgroundColor);
    virtual cqColor backgroundColor();
    
    virtual void setClipsToBounds(bool clipsToBounds);
    virtual bool clipsToBounds();
    
    virtual void setNeedsDisplay();
    
    virtual void drawRect(cqRect rect);
    
    virtual void renderAllOnScreen(cqSize screenSize);
    
    //hierarchy:
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

cq_class(cqViewLayerDelegate, cqLayerDelegate) {
    
    cq_as_proxy_of(cqView)
    
    void drawLayerInContext(cqLayerRef layer, cqContextRef context) override;
};

_CQAPPKIT_END_VERSION_NS
