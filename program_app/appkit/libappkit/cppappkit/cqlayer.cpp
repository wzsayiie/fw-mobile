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
    bool needsSuperDisplay = true;
    bool needsDisplay = true;
    
    cq_fbo *fbo = nullptr;
    float fw = 0;
    float fh = 0;
    
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
    } else if (dat->frame.origin != frame.origin) {
        dat->needsSuperDisplay = true;
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
        setNeedsDisplay();
    }
}

bool cqLayer::clipsToBounds() {
    return dat->clipsToBounds;
}

void cqLayer::setNeedsDisplay() {
    dat->needsDisplay = true;
}

static void mergeLayers(float x, float y, cqLayerRef layer) {
    cqRect f = layer->frame();
    float sx = f.origin.x + x;
    float sy = f.origin.y + y;
    float sw = f.size.width;
    float sh = f.size.height;
    
    cq_tex *tex = cq_fbo_tex(layer->dat->fbo);
    cq_draw_tex(sx, sy, sw, sh, tex);
    
    if (layer->clipsToBounds()) {
        return;
    }
    for (auto &it : layer->sublayers()) {
        mergeLayers(sx, sy, it);
    }
}

bool cqLayer::displayIfNeeded() {
    
    //sublayers drawn.
    bool sublayersDrawn = false;
    for (auto &it : dat->sublayers) {
        if (it->displayIfNeeded()) {
            sublayersDrawn = true;
        }
    }
    
    bool needsSuperDisplay = dat->needsSuperDisplay;
    bool needsDisplay = dat->needsDisplay;
    dat->needsSuperDisplay = false;
    dat->needsDisplay = false;
    
    if (sublayersDrawn && dat->clipsToBounds) {
        //need display cause sublayers' change.
    } else if (needsDisplay) {
        //need display cause own change.
    } else {
        return sublayersDrawn || needsSuperDisplay;
    }
    
    //remove deprecated fbo if needed.
    float w = dat->frame.size.width ;
    float h = dat->frame.size.height;
    if (w != dat->fw || h != dat->fh) {
        cq_del_fbo(dat->fbo);
        dat->fbo = nullptr;
        
        dat->fw = w;
        dat->fh = h;
    }
    
    //new fbo if needed.
    if (dat->fbo == nullptr && w > 0 && h > 0) {
        //make clearer with pixel size.
        float scale = cq_wnd_scale();
        dat->fbo = cq_new_fbo(w * scale, h *scale, NULL);
    }
    
    //draw:
    if (dat->fbo == nullptr) {
        return true;
    }
    cq_begin_draw_fbo(w, h, dat->fbo);
    
    //1. background.
    cqColor color = dat->backgroundColor;
    cq_clear_current(color.red, color.green, color.blue, color.alpha);
    
    //2. self.
    dat->delegate.drawLayerInContext(strongRef(), cqContext());
    
    //3. sublayers.
    if (dat->clipsToBounds) {
        for (auto &it : dat->sublayers) {
            mergeLayers(0, 0, it);
        }
    }
    
    cq_end_draw_fbo();
    return true;
}

void cqLayer::displayOnScreen(float w, float h) {
    displayIfNeeded();
    
    cq_begin_draw_fbo(w, h, CQ_SCREEN_FBO);
    cq_clear_current(1, 1, 1, 1);
    cq_draw_tex(0, 0, w, h, cq_fbo_tex(dat->fbo));
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
    
    if (dat->clipsToBounds) {
        setNeedsDisplay();
    }
}

void cqLayer::removeFromSuperlayer() {
    auto superlayer = dat->superlayer.lock();
    if (superlayer != nullptr) {
        cqVector::erase(&superlayer->dat->sublayers, strongRef());
        dat->superlayer.reset();
        
        if (superlayer->clipsToBounds()) {
            superlayer->setNeedsDisplay();
        }
    }
}
