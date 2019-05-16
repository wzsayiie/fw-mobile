#include "cqtouchevent_p.hh"

cq_member(cqTouchEvent) {
};

cqTouchEvent::cqTouchEvent() {
}

cqEventType cqTouchEvent::type() {
    return cqEventTypeTouches;
}
