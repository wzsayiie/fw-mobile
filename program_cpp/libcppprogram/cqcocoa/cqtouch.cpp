#include "cqtouch.hh"
#include "cqwindow.hh"

cq_member(cqTouch) {
    cqWindowWeakRef locatedWindow;
    cqPoint locationInWindow;
};

cqTouchRef cqTouch::createWithLocation(cqWindowRef window, cqPoint location) {
    cqTouchRef touch = cqTouch::create();
    touch->dat->locatedWindow = window;
    touch->dat->locationInWindow = location;
    return touch;
}

cqPoint cqTouch::locationInView(cqViewRef view) {
    if (view != nullptr) {
        auto location = dat->locationInWindow;
        auto window = dat->locatedWindow.lock();
        return view->convertPointFromView(location, window);
    } else {
        return cqPoint();
    }
}
