#include "cqtouchesevent_p.hh"

cq_member(cqTouchesEvent) {
};

cqTouchesEvent::cqTouchesEvent() {
}

cqEventType cqTouchesEvent::type() {
    return cqEventTypeTouches;
}
