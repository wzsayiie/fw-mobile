#include "cqtouch.hh"
#include "cqwindow.hh"

cq_member(cqTouch) {
    cqWindowWeakRef locatedWindow;
    cqPoint locationInWindow;
};

void cqTouch::init() {
    init(nullptr, cqPoint());
}

void cqTouch::init(cqWindowRef window, cqPoint location) {
    super::init();
    
    dat->locatedWindow = window;
    dat->locationInWindow = location;
}

cqPoint cqTouch::locationInView(cqViewRef view) {
    if (!dat->locatedWindow.expired() && view != nullptr) {
        auto location = dat->locationInWindow;
        auto window = dat->locatedWindow.lock();
        return view->convertPointFromView(location, window);
    } else {
        return cqPoint();
    }
}
