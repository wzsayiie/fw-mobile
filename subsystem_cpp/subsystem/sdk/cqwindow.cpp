#include "cqwindow.hh"
#include "cqhostapi.h"

struct _self_cqWindow {
    cqViewController::ref rootViewController;
    cq_window *window;
};

cqWindow::cqWindow() {
}

void cqWindow::setRootViewController(cqViewController::ref controller) {
    self->rootViewController = controller;
}

cqViewController::ref cqWindow::rootViewController() {
    return self->rootViewController;
}

void cqWindow::makeKeyAndVisible() {
}
