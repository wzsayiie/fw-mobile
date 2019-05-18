#include "cqwindow.hh"
#include "cqapplication.hh"
#include "cqosapi.h"
#include "cqtouchevent_p.hh"

cq_member(cqWindow) {
    cq_window *window = nullptr;
    cqViewControllerRef rootViewController;
    cqViewRef touchesResponder;
};

cqWindow::cqWindow() {
}

void cqWindow::setRootViewController(cqViewControllerRef controller) {
    if (dat->rootViewController == controller) {
        return;
    }
    
    if (dat->rootViewController != nullptr) {
        dat->rootViewController->view()->removeFromSuperview();
    }
    dat->rootViewController = controller;
    addSubview(dat->rootViewController->view());
}

cqViewControllerRef cqWindow::rootViewController() {
    return dat->rootViewController;
}

static void load(cq_window *window) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self == nullptr) {
        return;
    }
    
    cqRect rect; {
        rect.size.width  = cq_window_get_width (window);
        rect.size.height = cq_window_get_height(window);
    }
    self->setFrame(rect);
    cq_window_set_back_color(window, 1, 1, 1);
}

static void show(cq_window *window) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self == nullptr) {
        return;
    }
    
    auto delegate = cqApplication::sharedApplication()->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidBecomeActive();
    }
    cqViewControllerRef controller = self->rootViewController();
    if (controller != nullptr) {
        controller->viewDidAppear();
    }
}

static void hide(cq_window *window) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self == nullptr) {
        return;
    }
    
    auto delegate = cqApplication::sharedApplication()->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidEnterBackground();
    }
    cqViewControllerRef controller = self->rootViewController();
    if (controller != nullptr) {
        controller->viewDidDisappear();
    }
}

static void touchBegan(cq_window *window, float x, float y) {
    //hit test
    auto self = (cqWindow *)cq_window_get_extra(window);
    auto view = self->hitTest(cqPoint(x, y), cqTouchEvent::create());
    if (view == nullptr) {
        return;
    }
    
    //began event
    self->dat->touchesResponder = view;
    
    std::set<cqTouchRef> touches = { cqTouch::create() };
    auto event = cqTouchEvent::create();
    view->touchesBegan(touches, event);
}

static void touchMoved(cq_window *window, float x, float y) {
    auto dat = ((cqWindow *)cq_window_get_extra(window))->dat;
    if (dat->touchesResponder == nullptr) {
        return;
    }
    
    std::set<cqTouchRef> touches = { cqTouch::create() };
    auto event = cqTouchEvent::create();
    dat->touchesResponder->touchesMoved(touches, event);
}

static void touchEnded(cq_window *window, float x, float y) {
    auto dat = ((cqWindow *)cq_window_get_extra(window))->dat;
    if (dat->touchesResponder == nullptr) {
        return;
    }
    
    std::set<cqTouchRef> touches = { cqTouch::create() };
    auto event = cqTouchEvent::create();
    dat->touchesResponder->touchesEnded(touches, event);
}

void cqWindow::makeKeyAndVisible() {
    
    //NOTE: currently only one window be supported in a app.
    dat->window = cq_window_get_default();

    cq_window_set_extra(dat->window, (int64_t)this);
    
    cq_window_get_procedure(dat->window)->load = load;
    cq_window_get_procedure(dat->window)->show = show;
    cq_window_get_procedure(dat->window)->hide = hide;
    cq_window_get_procedure(dat->window)->touch_began = touchBegan;
    cq_window_get_procedure(dat->window)->touch_moved = touchMoved;
    cq_window_get_procedure(dat->window)->touch_ended = touchEnded;
}

cqResponderRef cqWindow::nextResponder() {
    return cqApplication::sharedApplication();
}

void cqWindow::setFrame(cqRect frame) {
    super::setFrame(frame);
    if (dat->rootViewController != nullptr) {
        dat->rootViewController->view()->setFrame(frame);
    }
}
