#include "rootviewcontroller.hh"
#include "cqlog.hh"

struct _self_RootViewController {
};

RootViewController::RootViewController() {
}

void RootViewController::viewDidLoad() {
    super::viewDidLoad();
    I("view load");
}

void RootViewController::viewDidAppear() {
    super::viewDidAppear();
    I("view appear");
}

void RootViewController::viewDidDisappear() {
    super::viewDidDisappear();
    I("view disappear");
}
