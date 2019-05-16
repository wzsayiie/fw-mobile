#include "cqview.hh"

cq_member(cqView) {
    cqRect frame;
    cqView::WeakRef superview;
    std::vector<cqView::Ref> subviews;
    cqResponder::WeakRef viewDelegate;
};

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

cqView::Ref cqView::superview() {
    return dat->superview.lock();
}

const std::vector<cqView::Ref> &cqView::subviews() {
    return dat->subviews;
}

void cqView::addSubview(cqView::Ref subview) {
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
        std::remove_if(brothers.begin(), brothers.end(), [=](cqView::Ref it) {
            return it.get() == this;
        });
        dat->superview.reset();
    }
}

cqView::Ref cqView::hitTest(cqPoint point, cqEvent::Ref event) {
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

bool cqView::pointInside(cqPoint point, cqEvent::Ref event) {
    return bounds().contains(point);
}

void cqView::setViewDelegate(cqResponder::Ref viewDelegate) {
    dat->viewDelegate = viewDelegate;
}

cqResponder::Ref cqView::viewDelegate() {
    return dat->viewDelegate.lock();
}

cqResponder::Ref cqView::nextResponder() {
    if (!dat->viewDelegate.expired()) {
        return dat->viewDelegate.lock();
    } else {
        return dat->superview.lock();
    }
}
