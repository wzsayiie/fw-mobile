#include "cqview.hh"
#include "cqviewcontroller.hh"
#include "cqwindow.hh"

//view:

cq_member(cqView) {
    cqLayerRef layer;
    
    cqViewWeakRef superview;
    std::vector<cqViewRef> subviews;
    cqViewControllerWeakRef viewController;
};

void cqView::init() {
    init(cqRect());
}

void cqView::init(cqRect frame) {
    super::init();
    
    dat->layer = cqLayer::create();
    dat->layer->setDelegate(cqViewLayerDelegate::create(strongRef()));
    
    setFrame(frame);
}

//position:

void cqView::setFrame(cqRect frame) {
    dat->layer->setFrame(frame);
}

cqRect cqView::frame() {
    return dat->layer->frame();
}

cqRect cqView::bounds() {
    return dat->layer->bounds();
}

void cqView::setCenter(cqPoint point) {
    cqRect f = frame();
    f.origin.x = point.x - f.size.width  / 2;
    f.origin.y = point.y - f.size.height / 2;
    setFrame(f);
}

cqPoint cqView::center() {
    cqRect f = frame();
    float x = f.origin.x + f.size.width  / 2;
    float y = f.origin.y + f.size.height / 2;
    return cqPoint(x, y);
}

//draw:

cqLayerRef cqView::layer() {
    return dat->layer;
}

void cqView::setBackgroundColor(cqColor backgroundColor) {
    dat->layer->setBackgroundColor(backgroundColor);
}

cqColor cqView::backgroundColor() {
    return dat->layer->backgroundColor();
}

void cqView::setClipsToBounds(bool clipsToBounds) {
    dat->layer->setClipsToBounds(clipsToBounds);
}

bool cqView::clipsToBounds() {
    return dat->layer->clipsToBounds();
}

void cqView::setNeedsDisplay() {
    dat->layer->setNeedsDisplay();
}

void cqView::drawRect(cqRect rect) {
}

void cqView::renderAllOnScreen(cqSize screenSize) {
    dat->layer->renderAllOnScreen(screenSize);
}

//hierarchy:

cqWindowRef cqView::window() {
    cqViewRef it = strongRef();
    while (it->superview() != nullptr) {
        it = it->superview();
    }
    
    if (it->isKindOfClass(cqWindow::clazz())) {
        return cqObject::cast<cqWindow>(it);
    } else {
        return nullptr;
    }
}

cqViewRef cqView::superview() {
    return dat->superview.lock();
}

const std::vector<cqViewRef> &cqView::subviews() {
    return dat->subviews;
}

void cqView::addSubview(cqViewRef subview) {
    if (subview == nullptr) {
        return;
    }
    if (subview.get() == this) {
        return;
    }
    
    //add view.
    subview->removeFromSuperview();
    subview->dat->superview = weakRef();
    dat->subviews.push_back(subview);
    
    //add layer.
    dat->layer->addSublayer(subview->layer());
}

void cqView::removeFromSuperview() {
    //remove view.
    auto superview = dat->superview.lock();
    if (superview != nullptr) {
        cqVector::erase(&superview->dat->subviews, strongRef());
        dat->superview.reset();
    }
    
    //remove layer.
    dat->layer->removeFromSuperlayer();
}

void cqView::setViewController(cqViewControllerRef viewController) {
    dat->viewController = viewController;
}

cqViewControllerRef cqView::viewController() {
    return dat->viewController.lock();
}

cqResponderRef cqView::nextResponder() {
    if (!dat->viewController.expired()) {
        return dat->viewController.lock();
    } else {
        return dat->superview.lock();
    }
}

//hit test:

static cqWindowRef offsetOnWindow(cqViewRef self, cqPoint *offset) {
    *offset = self->frame().origin;
    
    auto view = self;
    for (; view->superview(); view = view->superview()) {
        cqPoint origin = view->superview()->frame().origin;
        offset->x += origin.x;
        offset->y += origin.y;
    }
    
    if (view->isKindOfClass(cqWindow::clazz())) {
        return cqObject::cast<cqWindow>(view);
    } else {
        return nullptr;
    }
}

cqPoint cqView::convertPointFromView(cqPoint point, cqViewRef view) {
    if (view == nullptr) {
        return point;
    }
    
    cqPoint thisOffset;
    cqPoint thatOffset;
    cqWindowRef thisWindow = offsetOnWindow(strongRef(), &thisOffset);
    cqWindowRef thatWindow = offsetOnWindow(view       , &thatOffset);
    if (thisWindow == thatWindow && thisWindow != nullptr) {
        point.x += thatOffset.x - thisOffset.x;
        point.y += thatOffset.y - thisOffset.y;
    }
    return point;
}

cqPoint cqView::convertPointToView(cqPoint point, cqViewRef view) {
    if (view == nullptr) {
        return point;
    }
    
    cqPoint thisOffset;
    cqPoint thatOffset;
    cqWindowRef thisWindow = offsetOnWindow(strongRef(), &thisOffset);
    cqWindowRef thatWindow = offsetOnWindow(view       , &thatOffset);
    if (thisWindow == thatWindow && thisWindow != nullptr) {
        point.x += thisOffset.x - thatOffset.x;
        point.y += thisOffset.y - thatOffset.y;
    }
    return point;
}

cqViewRef cqView::hitTest(cqPoint point, cqEventRef event) {
    if (!pointInside(point, event)) {
        return nullptr;
    }

    for (auto &subview : subviews()) {
        cqPoint offset = subview->frame().origin;
        cqPoint touch = {point.x - offset.x, point.y - offset.y};
        auto target = subview->hitTest(touch, event);
        if (target != nullptr) {
            return target;
        }
    }
    return strongRef();
}

bool cqView::pointInside(cqPoint point, cqEventRef event) {
    return bounds().contains(point);
}

//view's layer delegate:

cq_member(cqViewLayerDelegate) {
};

void cqViewLayerDelegate::drawLayerInContext(cqLayerRef layer, cqContext context) {
    if (auto view = castCore()) {
        view->drawRect(view->bounds());
    }
}
