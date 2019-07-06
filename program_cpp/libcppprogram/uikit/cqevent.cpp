#include "cqevent.hh"

cq_member(cqEvent) {
};

cqEventType cqEvent::type() {
    return cqEventTypeTouches;
}
