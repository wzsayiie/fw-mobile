#include "cqwindow.hh"
#include "cqapplication.hh"

struct _self_cqWindow {
    cqViewController::ref rootViewController;
    cq_window *window = nullptr;
};

cqWindow::cqWindow() {
}

void cqWindow::setRootViewController(cqViewController::ref controller) {
    self->rootViewController = controller;
}

cqViewController::ref cqWindow::rootViewController() {
    return self->rootViewController;
}

static void cqWindow_load(cq_window *window) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self == nullptr) {
        return;
    }
    
    cqViewController::ref controller = self->rootViewController();
    if (controller != nullptr) {
        controller->viewDidLoad();
    }
}

static void cqWindow_show(cq_window *window) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self == nullptr) {
        return;
    }
    
    auto delegate = cqApplication::sharedApplication()->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidBecomeActive();
    }
    cqViewController::ref controller = self->rootViewController();
    if (controller != nullptr) {
        controller->viewDidAppear();
    }
}

static void cqWindow_hide(cq_window *window) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self == nullptr) {
        return;
    }
    
    auto delegate = cqApplication::sharedApplication()->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidEnterBackground();
    }
    cqViewController::ref controller = self->rootViewController();
    if (controller != nullptr) {
        controller->viewDidDisappear();
    }
}

static void cqWindow_touchBegan(cq_window *window, float x, float y) {
}

static void cqWindow_touchMoved(cq_window *window, float x, float y) {
}

static void cqWindow_touchEnded(cq_window *window, float x, float y) {
}

void cqWindow::setHostWindow(cq_window *window) {
    self->window = window;
    
    cq_window_set_back_color(window, 1, 1, 1);
    cq_window_set_extra(window, (int64_t)this);
    
    cq_window_get_procedure(window)->load = cqWindow_load;
    cq_window_get_procedure(window)->show = cqWindow_show;
    cq_window_get_procedure(window)->hide = cqWindow_hide;
    
    cq_window_get_procedure(window)->touch_began = cqWindow_touchBegan;
    cq_window_get_procedure(window)->touch_moved = cqWindow_touchMoved;
    cq_window_get_procedure(window)->touch_ended = cqWindow_touchEnded;
}
