#pragma once

#include "cqresponder.hh"
#include "cqcolor.hh"

_CQAPPKIT_BEGIN_VERSION_NS

//context:

struct cqContext {
    static cqContext currentContext();
};

//layer delegate:

cq_declare(cqLayer);

cq_class(cqLayerDelegate, cqProxy) {
    
    virtual void drawLayerInContext(cqLayerRef layer, cqContext context) {}
};

//layer:

cq_class(cqLayer, cqObject) {
    
    ~cqLayer();
    
    //delegate:
    virtual void setDelegate(cqLayerDelegateRef delegate);
    virtual cqLayerDelegateRef delegate();
    
    //position:
    virtual void setFrame(cqRect frame);
    virtual cqRect frame();
    virtual cqRect bounds();
    
    //draw:
    virtual void setBackgroundColor(cqColor backgroundColor);
    virtual cqColor backgroundColor();
    
    virtual void setClipsToBounds(bool clipsToBounds);
    virtual bool clipsToBounds();
    
    virtual void setNeedsDisplay();
    virtual void displayIfNeeded();
    
    virtual void renderAllOnScreen(cqSize screenSize);
    
    //hierarchy:
    virtual cqLayerRef superlayer();
    virtual const std::vector<cqLayerRef> &sublayers();
    virtual void addSublayer(cqLayerRef sublayer);
    virtual void removeFromSuperlayer();
};

_CQAPPKIT_END_VERSION_NS
