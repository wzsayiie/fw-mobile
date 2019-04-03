#include "cqwindow.hh"
#include "cqapplication.hh"
#include "cqhostapi.h"

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
    
    auto self = (cqWindow *)window->user_data;
    self->rootViewController()->viewDidLoad();
}

static void cqWindow_show(cq_window *window) {
    
    auto application = cqApplication::sharedApplication().get();
    application->delegate()->applicationDidBecomeActive();
    
    auto self = (cqWindow *)window->user_data;
    self->rootViewController()->viewDidAppear();
}

static void cqWindow_hide(cq_window *window) {
    
    auto application = cqApplication::sharedApplication().get();
    application->delegate()->applicationDidEnterBackground();
    
    auto self = (cqWindow *)window->user_data;
    self->rootViewController()->viewDidDisappear();
}

static void cqWindow_touchBegan(cq_window *window, float x, float y) {
}

static void cqWindow_touchMoved(cq_window *window, float x, float y) {
}

static void cqWindow_touchEnded(cq_window *window, float x, float y) {
}

void cqWindow::makeKeyAndVisible() {
    
    //create
    cq_window *window = cq_window_create();
    
    //configurate
    cq_window_set_back_color(window, 1, 1, 1);
    window->user_data = (int64_t)this;
    
    window->procedure.load = cqWindow_load;
    window->procedure.show = cqWindow_show;
    window->procedure.hide = cqWindow_hide;
    
    window->procedure.touch_began = cqWindow_touchBegan;
    window->procedure.touch_moved = cqWindow_touchMoved;
    window->procedure.touch_ended = cqWindow_touchEnded;
    
    //show
    cq_window_load(window);
    self->window = window;
}
