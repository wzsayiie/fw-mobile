#include "cqwindow.hh"
#include "cqhost_p.hh"

struct _self_CQWindow {
    CQViewController::ref rootViewController;
};

CQWindow::CQWindow() {
}

void CQWindow::setRootViewController(CQViewController::ref controller) {
    self->rootViewController = controller;
}

CQViewController::ref CQWindow::rootViewController() {
    return self->rootViewController;
}

static void onUILoad(shared_ptr<_self_CQWindow> self) {
    if (self->rootViewController) {
        self->rootViewController->viewDidLoad();
    }
}

static void onUIAppear(shared_ptr<_self_CQWindow> self) {
    if (self->rootViewController) {
        self->rootViewController->viewDidAppear();
    }
}

static void onUIDisappear(shared_ptr<_self_CQWindow> self) {
    if (self->rootViewController) {
        self->rootViewController->viewDidDisappear();
    }
}

void CQWindow::makeKeyAndVisible() {

    CQHostAddListener(CQHostEventUILoad     , bind(onUILoad     , self));
    CQHostAddListener(CQHostEventUIAppear   , bind(onUIAppear   , self));
    CQHostAddListener(CQHostEventUIDisappear, bind(onUIDisappear, self));
}
