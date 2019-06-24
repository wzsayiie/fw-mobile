#include "cqwindow.hh"
#include "cqapplication.hh"
#include "cqopengl.h"
#include "cqtouchesevent_p.hh"
#include "cqwindow.h"

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
    auto self = (cqWindow *)cq_window_extra(window);
    if (self == nullptr) {
        return;
    }
    
    cqRect rect; {
        rect.size.width  = cq_window_width (window);
        rect.size.height = cq_window_height(window);
    }
    self->setFrame(rect);
}

static void appear(cq_window *window) {
    auto self = (cqWindow *)cq_window_extra(window);
    if (self == nullptr) {
        return;
    }
    
    auto delegate = cqApplication::get()->delegate();
    if (delegate != nullptr) {
        delegate->applicationWillEnterForeground();
    }
}

static void disappear(cq_window *window) {
    auto self = (cqWindow *)cq_window_extra(window);
    if (self == nullptr) {
        return;
    }
    
    auto delegate = cqApplication::get()->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidEnterBackground();
    }
}

static void resize(cq_window *window, float width, float height) {
    auto self = (cqWindow *)cq_window_extra(window);
    if (self == nullptr) {
        return;
    }
    
    self->setFrame(cqRect(0, 0, width, height));
}

static void glpaint(cq_window *window) {
    auto self = (cqWindow *)cq_window_extra(window);
    if (self == nullptr) {
        return;
    }
    
    glClearColor(0.6, 0.9, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void pbegan(cq_window *window, float x, float y) {
    auto self = (cqWindow *)cq_window_extra(window);
    
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

static void pmoved(cq_window *window, float x, float y) {
    auto self = (cqWindow *)cq_window_extra(window);
    if (self->dat->touchesResponder == nullptr) {
        return;
    }
    
    std::set<cqTouchRef> touches = {
        cqTouch::createWithLocation(self->strongRef(), cqPoint(x, y))
    };
    cqTouchesEventRef touchesEvent = cqTouchesEvent::create();
    
    self->dat->touchesResponder->touchesMoved(touches, touchesEvent);
}

static void pended(cq_window *window, float x, float y) {
    auto self = (cqWindow *)cq_window_extra(window);
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
    
    cq_procedure procedure = {nullptr};
    procedure.load = load;
    procedure.appear = appear;
    procedure.disappear = disappear;
    procedure.resize = resize;
    procedure.glpaint = glpaint;
    procedure.pbegan = pbegan;
    procedure.pmoved = pmoved;
    procedure.pended = pended;
    
    dat->window = cq_create_window();
    cq_set_procedure(dat->window, &procedure);
    cq_set_window_extra(dat->window, (int64_t)this);
    cq_show_window(dat->window);
}

cqResponderRef cqWindow::nextResponder() {
    return cqApplication::get();
}

void cqWindow::setFrame(cqRect frame) {
    super::setFrame(frame);
    if (dat->rootViewController != nullptr) {
        dat->rootViewController->view()->setFrame(frame);
    }
}
