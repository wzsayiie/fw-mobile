#include "cqapplication.hh"

cq_member(cqApplication) {
    cqApplicationDelegate::ref delegate;
    cqWindow::ref window;
};

cqApplication::ref cqApplication::sharedApplication() {
    static cqApplication::ref object;
    if (object == nullptr) {
        object = cqApplication::create();
    }
    return object;
}

cqApplication::cqApplication() {
}

void cqApplication::setDelegate(cqApplicationDelegate::ref delegate) {
    self->delegate = delegate;
}

cqApplicationDelegate::ref cqApplication::delegate() {
    return self->delegate;
}

void cqApplication::setWindow(cqWindow::ref window) {
    self->window = window;
}

cqWindow::ref cqApplication::window() {
    return self->window;
}

void cqApplicationMain(cqApplicationDelegate::ref delegate) {
    auto application = cqApplication::sharedApplication();
    application->setDelegate(delegate);
}

void _cq_default_window_created(cq_window *window) {
    _entry();
    
    auto win = cqWindow::create();
    win->setHostWindow(window);
    
    auto application = cqApplication::sharedApplication();
    application->setWindow(win);
    
    auto delegate = application->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidFinishLaunching(win);
    }
}
