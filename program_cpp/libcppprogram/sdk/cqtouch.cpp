#include "cqtouch.hh"

cq_member(cqTouch) {
    cqWindowWeakRef locatedWindow;
    cqPoint locationInWindow;
};

cqTouch::cqTouch() {
}

void cqTouch::setLocationInWindow(cqWindowRef window, cqPoint location) {
    dat->locatedWindow = window;
    dat->locationInWindow = location;
}

cqPoint cqTouch::locationInView(cqViewRef view) {
    return cqPoint();
}
