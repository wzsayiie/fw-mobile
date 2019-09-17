#include "cqview.hh"
#include "cqgraphics.hh"
#include "cqviewcontroller.hh"
#include "cqwindow.hh"

cq_member(cqView) {
    cqRect frame;
    
    cqColor backgroundColor;
    
    cqViewWeakRef superview;
    std::vector<cqViewRef> subviews;
    cqViewControllerWeakRef viewController;
};

cqViewRef cqView::createWithFrame(cqRect frame) {
    cqViewRef view = cqView::create();
    view->setFrame(frame);
    return view;
}

void cqView::setFrame(cqRect frame) {
    dat->frame = frame;
}

cqRect cqView::frame() {
    return dat->frame;
}

cqRect cqView::bounds() {
    return cqRect(cqPoint(), dat->frame.size);
}

void cqView::setBackgroundColor(cqColor backgroundColor) {
    dat->backgroundColor = backgroundColor;
}

cqColor cqView::backgroundColor() {
    return dat->backgroundColor;
}

void cqView::drawSelfAndSubviews() {
    cqRect rect = bounds();
    
    //draw self.
    drawBackgroundInRect(rect);
    drawInRect(rect);
    
    //draw subviews.
    for (cqViewRef sub : dat->subviews) {
        cqContext context = cqGraphics::currentContext();
        
        cqRect subFrame = sub->frame();
        cqContext subContext(
            context.offsetX + subFrame.origin.x,
            context.offsetY + subFrame.origin.y
        );
        cqGraphics::pushContext(subContext);
        sub->drawSelfAndSubviews();
        cqGraphics::popContext();
    }
}

void cqView::drawBackgroundInRect(cqRect rect) {
    cqColor color = dat->backgroundColor;
    
    bool isClearColor =
        cq_flt_equal(color.red  , 0) &&
        cq_flt_equal(color.green, 0) &&
        cq_flt_equal(color.blue , 0) &&
        cq_flt_equal(color.alpha, 0);
    
    if (!isClearColor) {
        cqContext context = cqGraphics::currentContext();
        context.setFillColor(color);
        context.fillRect(rect);
    }
}

void cqView::drawInRect(cqRect rect) {
}

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
    
    subview->removeFromSuperview();
    subview->dat->superview = weakRef();
    dat->subviews.push_back(subview);
}

void cqView::removeFromSuperview() {
    auto superview = dat->superview.lock();
    if (superview != nullptr) {
        auto brothers = superview->dat->subviews;
        std::remove_if(brothers.begin(), brothers.end(), [=](cqViewRef it) {
            return it.get() == this;
        });
        dat->superview.reset();
    }
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
