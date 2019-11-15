#include "cqlayer.hh"
#include "cqglkit.h"

//context:

cqContext cqGraphics::currentContext() {
    return cqContext();
}

//layer delegate:

cq_member(cqObject_LayerDelegate) {
};

cq_member(cqResponder_LayerDelegate) {
};

cqLayerDelegate::cqLayerDelegate() {
    _type = Type::Null;
    //_object = nullptr;
}

cqLayerDelegate::cqLayerDelegate(cqObject_LayerDelegateRef object) {
    _type = Type::Object;
    _object = object;
}

cqLayerDelegate::cqLayerDelegate(cqResponder_LayerDelegateRef object) {
    _type = Type::Responder;
    _object = object;
}

void cqLayerDelegate::drawLayerInContext(cqLayerRef layer, cqContext context) {

    cqObject_LayerDelegateRef    obj;
    cqResponder_LayerDelegateRef rep;
    switch (_type) {
        case Type::Object   : obj = cqObject::cast<cqObject_LayerDelegate   >(_object.lock()); break;
        case Type::Responder: rep = cqObject::cast<cqResponder_LayerDelegate>(_object.lock()); break;
        default:;
    }
    
    if /**/ (obj) { obj->drawLayerInContext(layer, context); }
    else if (rep) { rep->drawLayerInContext(layer, context); }
}

//layer:

cq_member(cqLayer) {
    cqLayerDelegate delegate;
    
    cqRect frame;
    
    cqColor backgroundColor;
    bool clipsToBounds = false;
    bool needsDisplay = true;
    cq_fbo *fbo = nullptr;
    
    cqLayerWeakRef superlayer;
    std::vector<cqLayerRef> sublayers;
};

cqLayer::~cqLayer() {
    cq_del_fbo(dat->fbo);
}

//delegate:

void cqLayer::setDelegate(cqLayerDelegate delegate) {
    dat->delegate = delegate;
}

cqLayerDelegate cqLayer::delegate() {
    return dat->delegate;
}

//position:

void cqLayer::setFrame(cqRect frame) {
    if (dat->frame.size != frame.size) {
        setNeedsDisplay();
    }
    dat->frame = frame;
}

cqRect cqLayer::frame() {
    return dat->frame;
}

cqRect cqLayer::bounds() {
    return cqRect(cqPoint(), dat->frame.size);
}

//draw:

void cqLayer::setBackgroundColor(cqColor backgroundColor) {
    if (dat->backgroundColor != backgroundColor) {
        dat->backgroundColor = backgroundColor;
        setNeedsDisplay();
    }
}

cqColor cqLayer::backgroundColor() {
    return dat->backgroundColor;
}

void cqLayer::setClipsToBounds(bool clipsToBounds) {
    if (dat->clipsToBounds != clipsToBounds) {
        dat->clipsToBounds = clipsToBounds;
        //currently this function is unimplemented.
        //setNeedsDisplay();
    }
}

bool cqLayer::clipsToBounds() {
    return dat->clipsToBounds;
}

void cqLayer::setNeedsDisplay() {
    dat->needsDisplay = true;
}

void cqLayer::displayIfNeeded() {
    if (!dat->needsDisplay) {
        return;
    }
    dat->needsDisplay = false;
    
    //remove deprecated fbo if needed.
    float w = dat->frame.size.width;
    float h = dat->frame.size.height;
    auto pw = (int32_t)(w * cq_wnd_scale());
    auto ph = (int32_t)(h * cq_wnd_scale());
    
    if (dat->fbo != nullptr) {
        cq_tex *tex = cq_fbo_tex(dat->fbo);
        int32_t opw = cq_tex_pw(tex);
        int32_t oph = cq_tex_ph(tex);
        
        if (pw != opw || ph != oph) {
            cq_del_fbo(dat->fbo);
            dat->fbo = nullptr;
        }
    }
    
    //new fbo if needed.
    if (dat->fbo == nullptr) {
        dat->fbo = cq_new_fbo(pw, ph, NULL);
    }
    
    //draw.
    if (dat->fbo == nullptr) {
        return;
    }
    cq_begin_draw_fbo(w, h, dat->fbo);
    
    cqColor color = dat->backgroundColor;
    cq_clear_current(color.red, color.green, color.blue, color.alpha);
    dat->delegate.drawLayerInContext(strongRef(), cqContext());
    
    cq_end_draw_fbo();
}

static void displayRecursively(cqLayerRef layer) {
    //self.
    layer->displayIfNeeded();
    
    //sublayers.
    for (auto &it : layer->sublayers()) {
        displayRecursively(it);
    }
}

static void renderRecursively(cqPoint offset, cqLayerRef layer) {
    //self.
    cqPoint off = layer->frame().origin + offset;
    cqSize size = layer->frame().size;
    cq_tex *tex = cq_fbo_tex(layer->dat->fbo);
    cq_draw_tex(off.x, off.y, size.width, size.height, tex);
    
    //sublayers.
    for (auto &it : layer->sublayers()) {
        renderRecursively(off, it);
    }
}

void cqLayer::renderAllOnScreen(cqSize screenSize) {
    displayRecursively(strongRef());
    
    cq_begin_draw_fbo(screenSize.width, screenSize.height, CQ_SCREEN_FBO);
    cq_clear_current(1, 1, 1, 1);
    renderRecursively(cqPoint(), strongRef());
    cq_end_draw_fbo();
}

//hierarchy:

cqLayerRef cqLayer::superlayer() {
    return dat->superlayer.lock();
}

const std::vector<cqLayerRef> &cqLayer::sublayers() {
    return dat->sublayers;
}

void cqLayer::addSublayer(cqLayerRef sublayer) {
    if (sublayer == nullptr) {
        return;
    }
    if (sublayer.get() == this) {
        return;
    }
    
    sublayer->removeFromSuperlayer();
    sublayer->dat->superlayer = weakRef();
    dat->sublayers.push_back(sublayer);
}

void cqLayer::removeFromSuperlayer() {
    auto superlayer = dat->superlayer.lock();
    if (superlayer != nullptr) {
        cqVector::erase(&superlayer->dat->sublayers, strongRef());
        dat->superlayer.reset();
    }
}
