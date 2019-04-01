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
    
    auto self = (cqWindow *)cq_window_get_extra(window);
    self->rootViewController()->viewDidLoad();
}

static void cqWindow_show(cq_window *window) {
    
    auto application = cqApplication::sharedApplication().get();
    application->delegate()->applicationDidBecomeActive();
    
    auto self = (cqWindow *)cq_window_get_extra(window);
    self->rootViewController()->viewDidAppear();
}

static void cqWindow_hide(cq_window *window) {
    
    auto application = cqApplication::sharedApplication().get();
    application->delegate()->applicationDidEnterBackground();
    
    auto self = (cqWindow *)cq_window_get_extra(window);
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
    cq_window_set_extra(window, this);
    
    cq_window_get_procedure(window)->load = cqWindow_load;
    cq_window_get_procedure(window)->show = cqWindow_show;
    cq_window_get_procedure(window)->hide = cqWindow_hide;
    
    cq_window_get_procedure(window)->touch_began = cqWindow_touchBegan;
    cq_window_get_procedure(window)->touch_moved = cqWindow_touchMoved;
    cq_window_get_procedure(window)->touch_ended = cqWindow_touchEnded;
    
    //show
    cq_window_load(window);
    self->window = window;
}
