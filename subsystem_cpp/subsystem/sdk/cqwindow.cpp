#include "cqwindow.hh"
#include "cqapplication.hh"
#include "cqhostapi.h"

static cqApplication *sApplication = nullptr;
static cqWindow *sWindow = nullptr;

struct _self_cqWindow {
    cqViewController::ref rootViewController;
    cq_window *window = nullptr;
};

cqWindow::cqWindow() {
    sApplication = cqApplication::sharedApplication().get();
    sWindow = this;
}

void cqWindow::setRootViewController(cqViewController::ref controller) {
    self->rootViewController = controller;
}

cqViewController::ref cqWindow::rootViewController() {
    return self->rootViewController;
}

static void cqWindow_load(cq_window *window) {
    sWindow->rootViewController()->viewDidLoad();
}

static void cqWindow_show(cq_window *window) {
    sApplication->delegate()->applicationDidBecomeActive();
    sWindow->rootViewController()->viewDidAppear();
}

static void cqWindow_hide(cq_window *window) {
    sApplication->delegate()->applicationDidEnterBackground();
    sWindow->rootViewController()->viewDidDisappear();
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
    cq_window_set_background_color(window, 1, 1, 1);
    
    cq_window_get_procedure(window)->load = cqWindow_load;
    cq_window_get_procedure(window)->show = cqWindow_show;
    cq_window_get_procedure(window)->hide = cqWindow_hide;
    
    cq_window_get_procedure(window)->touch_began = cqWindow_touchBegan;
    cq_window_get_procedure(window)->touch_moved = cqWindow_touchMoved;
    cq_window_get_procedure(window)->touch_ended = cqWindow_touchEnded;
    
    //show
    cq_window_show(window);
    self->window = window;
}
