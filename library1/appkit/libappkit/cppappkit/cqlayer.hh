#pragma once

#include "cqresponder.hh"
#include "cqcolor.hh"

_CQAPPKIT_BEGIN_VERSION_NS

//context:

cq_declare(cqLayer);

struct cqContext {
};

struct cqGraphics {
    static cqContext currentContext();
};

//layer delegate:

cq_class(cqObject_LayerDelegate, cqObject) {
    
    virtual void drawLayerInContext(cqLayerRef layer, cqContext context) {}
};

cq_class(cqResponder_LayerDelegate, cqResponder) {
    
    virtual void drawLayerInContext(cqLayerRef layer, cqContext context) {}
};

struct cqLayerDelegate {
    
    enum class Type {
        Null      = 0,
        Object    = 1,
        Responder = 2,
    };
    
    Type _type;
    cqObjectWeakRef _object;
    
    cqLayerDelegate();
    cqLayerDelegate(cqObject_LayerDelegateRef object);
    cqLayerDelegate(cqResponder_LayerDelegateRef object);
    
    void drawLayerInContext(cqLayerRef layer, cqContext context);
};

//layer:

cq_class(cqLayer, cqObject) {
    
    ~cqLayer();
    
    //delegate:
    virtual void setDelegate(cqLayerDelegate delegate);
    virtual cqLayerDelegate delegate();
    
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
