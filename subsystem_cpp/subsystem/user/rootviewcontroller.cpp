#include "rootviewcontroller.hh"
#include "cqlog.hh"

struct _self_RootViewController {
};

RootViewController::RootViewController() {
}

void RootViewController::viewDidLoad() {
    super::viewDidLoad();
    ii("view load");
}

void RootViewController::viewDidAppear() {
    super::viewDidAppear();
    ii("view appear");
}

void RootViewController::viewDidDisappear() {
    super::viewDidDisappear();
    ii("view disappear");
}
