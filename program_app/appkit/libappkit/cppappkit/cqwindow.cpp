#include "cqwindow.hh"
#include "cqapplication.hh"
#include "cqgraphics.hh"
#include "cqtouchesevent_p.hh"
#include "cqwnd.h"

cq_member(cqWindow) {
    cq_wnd *wnd = nullptr;
    
    cqViewControllerRef rootViewController;
    cqViewRef touchesResponder;
};

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

static void load(cq_wnd *wnd) {
    auto self = (cqWindow *)cq_wnd_extra(wnd);
    
    cqRect rect; {
        rect.size.width  = cq_wnd_width (wnd);
        rect.size.height = cq_wnd_height(wnd);
    }
    self->setFrame(rect);
    
    cqGraphics::startupGraphicsProgram(self->strongRef());
}

static void appear(cq_wnd *wnd) {
    //auto self = (cqWindow *)cq_wnd_extra(wnd);
    
    auto delegate = cqApplication::get()->delegate();
    if (delegate != nullptr) {
        delegate->applicationWillEnterForeground();
    }
}

static void disappear(cq_wnd *wnd) {
    //auto self = (cqWindow *)cq_wnd_extra(wnd);
    
    auto delegate = cqApplication::get()->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidEnterBackground();
    }
}

static void resize(cq_wnd *wnd, float width, float height) {
    auto self = (cqWindow *)cq_wnd_extra(wnd);
    
    self->setFrame(cqRect(0, 0, width, height));
}

static void gldraw(cq_wnd *wnd) {
    auto self = (cqWindow *)cq_wnd_extra(wnd);
    
    cqGraphics::prepareDraw();
    
    cqGraphics::pushContext(cqContext(0, 0));
    self->drawSelfAndSubviews();
    cqGraphics::popContext();
}

static void pbegan(cq_wnd *wnd, float x, float y) {
    auto self = (cqWindow *)cq_wnd_extra(wnd);
    
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

static void pmoved(cq_wnd *wnd, float x, float y) {
    auto self = (cqWindow *)cq_wnd_extra(wnd);
    if (self->dat->touchesResponder == nullptr) {
        return;
    }
    
    std::set<cqTouchRef> touches = {
        cqTouch::createWithLocation(self->strongRef(), cqPoint(x, y))
    };
    cqTouchesEventRef touchesEvent = cqTouchesEvent::create();
    
    self->dat->touchesResponder->touchesMoved(touches, touchesEvent);
}

static void pended(cq_wnd *wnd, float x, float y) {
    auto self = (cqWindow *)cq_wnd_extra(wnd);
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
    
    cq_wndproc proc = {nullptr};
    proc.load = load;
    proc.appear = appear;
    proc.disappear = disappear;
    proc.resize = resize;
    proc.gldraw = gldraw;
    proc.pbegan = pbegan;
    proc.pmoved = pmoved;
    proc.pended = pended;
    
    dat->wnd = cq_new_wnd();
    cq_set_wndproc(dat->wnd, &proc);
    cq_set_wnd_extra(dat->wnd, (int64_t)this);
    cq_show_wnd(dat->wnd);
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
