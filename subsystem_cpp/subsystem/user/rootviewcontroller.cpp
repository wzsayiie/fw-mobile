#include "rootviewcontroller.h"

struct _self_RootViewController {
};

RootViewController::RootViewController() {
    C_INIT(self);
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
