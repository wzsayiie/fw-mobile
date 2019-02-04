#include "cwindow.h"
#include "chost_p.h"

struct _self_CWindow {
    CViewController::ref rootViewController;
};

static void onUIAppear(shared_ptr<_self_CWindow> self) {
    if (self->rootViewController) {
        self->rootViewController->viewDidAppear();
    }
}

static void onUIDisappear(shared_ptr<_self_CWindow> self) {
    if (self->rootViewController) {
        self->rootViewController->viewDidDisappear();
    }
}

CWindow::CWindow() {
    C_INIT(self);
}

void CWindow::setRootViewController(CViewController::ref controller) {
    self->rootViewController = controller;
}

CViewController::ref CWindow::rootViewController() {
    return self->rootViewController;
}

void CWindow::makeKeyAndVisible() {

    CHostAddListener(CHostEventUIAppear   , bind(onUIAppear   , self));
    CHostAddListener(CHostEventUIDisappear, bind(onUIDisappear, self));
    
    if (self->rootViewController != nullptr) {
        self->rootViewController->viewDidLoad();
    }
}
