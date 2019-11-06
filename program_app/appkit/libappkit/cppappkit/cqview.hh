#pragma once

#include "cqlayer.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_declare(cqViewController);
cq_declare(cqWindow);

cq_class(cqView, cqResponder_LayerDelegate) {
    
    static cqViewRef createWithFrame(cqRect frame);
    
    void init() override;
    
    //position:
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    //draw:
    virtual cqLayerRef layer();
    
    virtual void setBackgroundColor(cqColor backgroundColor);
    virtual cqColor backgroundColor();
    
    virtual void setClipsToBounds(bool clipsToBounds);
    virtual bool clipsToBounds();
    
    virtual void setNeedsDisplay();
    
    void drawLayerInContext(cqLayerRef layer, cqContext context) override;
    virtual void drawRect(cqRect rect);
    
    virtual void displayOnScreen(float w, float h);
    
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

_CQAPPKIT_END_VERSION_NS
