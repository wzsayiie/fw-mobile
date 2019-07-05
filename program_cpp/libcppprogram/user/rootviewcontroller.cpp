#include "rootviewcontroller.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"

cq_member(RootViewController) {
};

RootViewController::RootViewController() {
}

void RootViewController::viewDidLoad() {
    super::viewDidLoad();
}

void RootViewController::touchesBegan(
    const std::set<cqTouchRef> &touches, cqEventRef event)
{
}

void RootViewController::touchesMoved(
    const std::set<cqTouchRef> &touches, cqEventRef event)
{
}

void RootViewController::touchesEnded(
    const std::set<cqTouchRef> &touches, cqEventRef event)
{
}
