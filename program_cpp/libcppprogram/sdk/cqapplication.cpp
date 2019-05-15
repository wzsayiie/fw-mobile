#include "cqapplication.hh"
#include "cqosapi.h"

cq_member(cqApplication) {
    cqApplicationDelegate::ref delegate;
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

void cqApplicationMain(cqApplicationDelegate::ref delegate) {
    auto application = cqApplication::sharedApplication();
    application->setDelegate(delegate);
}

void _cq_default_window_created() {
    
    //call cqApplicationMain
    _entry();
    
    //call applicationDidFinishLaunching
    auto application = cqApplication::sharedApplication();
    auto delegate = application->delegate();
    if (delegate != nullptr) {
        delegate->applicationDidFinishLaunching();
    }
}
