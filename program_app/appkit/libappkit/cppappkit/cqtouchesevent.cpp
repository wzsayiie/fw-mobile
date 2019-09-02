#include "cqtouchesevent_p.hh"

cq_member(cqTouchesEvent) {
};

cqEventType cqTouchesEvent::type() {
    return cqEventTypeTouches;
}
