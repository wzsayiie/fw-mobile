#include "cqview.hh"

cq_member(cqView) {
    cqRect frame;
    cqView::weak_ref superview;
    std::vector<cqView::ref> subviews;
};

cqView::cqView() {
}

void cqView::setFrame(cqRect frame) {
    self->frame = frame;
}

cqRect cqView::frame() {
    return self->frame;
}

cqRect cqView::bounds() {
    return cqRect(cqPoint(), self->frame.size);
}

cqView::weak_ref cqView::superview() {
    return self->superview;
}

const std::vector<cqView::ref> &cqView::subviews() {
    return self->subviews;
}

void cqView::addSubview(cqView::ref subview) {
    if (subview == nullptr) {
        return;
    }
    
    subview->removeFromSuperview();
    subview->self->superview = weak();
    self->subviews.push_back(subview);
}

void cqView::removeFromSuperview() {
    auto superview = self->superview.lock();
    if (superview != nullptr) {
        auto brothers = superview->self->subviews;
        std::remove_if(brothers.begin(), brothers.end(), [=](cqView::ref it) {
            return it.get() == this;
        });
        self->superview.reset();
    }
}

cqView::ref cqView::hitTest(cqPoint point, cqEvent::ref event) {
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
    return weak().lock();
}

bool cqView::pointInside(cqPoint point, cqEvent::ref event) {
    return bounds().contains(point);
}
