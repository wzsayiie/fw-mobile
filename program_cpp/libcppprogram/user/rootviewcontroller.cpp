#include "rootviewcontroller.hh"

cq_member(RootViewController) {
};

RootViewController::RootViewController() {
}

void RootViewController::viewDidLoad() {
    super::viewDidLoad();
}

void RootViewController::viewDidAppear() {
    super::viewDidAppear();
}

void RootViewController::viewDidDisappear() {
    super::viewDidDisappear();
}

void RootViewController::touchesBegan
/**/(const std::set<cqTouchRef> &touches, cqEventRef event)
{
}

void RootViewController::touchesMoved
/**/(const std::set<cqTouchRef> &touches, cqEventRef event)
{
}

void RootViewController::touchesEnded
/**/(const std::set<cqTouchRef> &touches, cqEventRef event)
{
    cqTouchRef any = *touches.begin();
    cqPoint location = any->locationInView(view());
    I("touch location %s", cqStringFromPoint(location));
}
