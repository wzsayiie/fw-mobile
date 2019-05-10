#include "cqevent.hh"

cq_member(cqEvent) {
};

cqEvent::cqEvent() {
}

cqEventType cqEvent::type() {
    return cqEventTypeTouches;
}
