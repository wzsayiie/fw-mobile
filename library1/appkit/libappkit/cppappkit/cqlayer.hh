#pragma once

#include "cqcontext.hh"
#include "cqgeometry.hh"

_CQAPPKIT_BEGIN_VERSION_NS

//layer delegate:

cq_declare(cqLayer);

cq_class(cqLayerDelegate, cqProxy) {
    
    virtual void drawLayerInContext(cqLayerRef layer, cqContextRef context) {}
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
