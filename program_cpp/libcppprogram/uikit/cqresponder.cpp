#include "cqresponder.hh"

cq_member(cqResponder) {
};

cqResponderRef cqResponder::nextResponder() {
    return nullptr;
}

void cqResponder::touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event) {
    auto next = nextResponder();
    if (next != nullptr) {
        next->touchesBegan(touches, event);
    }
}

void cqResponder::touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event) {
    auto next = nextResponder();
    if (next != nullptr) {
        next->touchesMoved(touches, event);
    }
}

void cqResponder::touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event) {
    auto next = nextResponder();
    if (next != nullptr) {
        next->touchesEnded(touches, event);
    }
}
