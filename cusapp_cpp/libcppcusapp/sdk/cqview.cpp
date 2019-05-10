#include "cqview.hh"

cq_member(cqView) {
};

cqView::cqView() {
}

cqView::ref cqView::hitTest(cqPoint point, cqEvent::ref event) {
    return nullptr;
}

bool cqView::pointInside(cqPoint point, cqEvent::ref event) {
    return false;
}
