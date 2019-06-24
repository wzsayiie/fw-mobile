#include "cqview.hh"
#include "cqviewcontroller.hh"
#include "cqwindow.hh"

cq_member(cqView) {
    cqRect frame;
    cqViewWeakRef superview;
    std::vector<cqViewRef> subviews;
    cqViewControllerWeakRef viewController;
};

cqViewRef cqView::createWithFrame(cqRect frame) {
    cqViewRef view = cqView::create();
    view->setFrame(frame);
    return view;
}

cqView::cqView() {
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

cqWindowRef cqView::window() {
    cqViewRef it = strongRef();
    while (it->superview() != nullptr) {
        it = it->superview();
    }
    
    if (it->isKindOfClass(cqWindow::clazz(0))) {
        return it->cast<cqWindow>();
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

static cqWindowRef offsetOnWindow(cqViewRef self, cqPoint *offset) {
    *offset = self->frame().origin;
    
    auto view = self;
    for (; view->superview(); view = view->superview()) {
        cqPoint origin = view->superview()->frame().origin;
        offset->x += origin.x;
        offset->y += origin.y;
    }
    
    if (view->isKindOfClass(cqWindow::clazz(0))) {
        return view->cast<cqWindow>();
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

    for (auto subview : subviews()) {
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
