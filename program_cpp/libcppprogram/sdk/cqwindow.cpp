#include "cqwindow.hh"
#include "cqapplication.hh"
#include "cqosapi.h"
#include "cqtouchesevent_p.hh"

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
    auto self = (cqWindow *)cq_window_get_extra(window);
    
    std::set<cqTouchRef> touches = {
        cqTouch::createWithLocation(self->strongRef(), cqPoint(x, y))
    };
    cqTouchesEventRef touchesEvent = cqTouchesEvent::create();
    
    //hit test
    auto view = self->hitTest(cqPoint(x, y), touchesEvent);
    if (view == nullptr) {
        return;
    }
    
    //began event
    view->touchesBegan(touches, touchesEvent);
    self->dat->touchesResponder = view;
}

static void touchMoved(cq_window *window, float x, float y) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self->dat->touchesResponder == nullptr) {
        return;
    }
    
    std::set<cqTouchRef> touches = {
        cqTouch::createWithLocation(self->strongRef(), cqPoint(x, y))
    };
    cqTouchesEventRef touchesEvent = cqTouchesEvent::create();
    
    self->dat->touchesResponder->touchesMoved(touches, touchesEvent);
}

static void touchEnded(cq_window *window, float x, float y) {
    auto self = (cqWindow *)cq_window_get_extra(window);
    if (self->dat->touchesResponder == nullptr) {
        return;
    }
    
    std::set<cqTouchRef> touches = {
        cqTouch::createWithLocation(self->strongRef(), cqPoint(x, y))
    };
    cqTouchesEventRef touchesEvent = cqTouchesEvent::create();
    
    self->dat->touchesResponder->touchesEnded(touches, touchesEvent);
    self->dat->touchesResponder.reset();
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
