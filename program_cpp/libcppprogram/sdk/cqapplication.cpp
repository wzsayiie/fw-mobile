#include "cqapplication.hh"
#include "cqosapi.h"

cq_member(cqApplicationDelegate) {
};

cqApplicationDelegate::cqApplicationDelegate() {
}

void cqApplicationDelegate::applicationDidFinishLaunching() {}
void cqApplicationDelegate::applicationDidBecomeActive   () {}
void cqApplicationDelegate::applicationDidEnterBackground() {}

cq_member(cqApplication) {
    cqApplicationDelegate::Ref delegate;
};

cqApplication::Ref cqApplication::sharedApplication() {
    static cqApplication::Ref object;
    if (object == nullptr) {
        object = cqApplication::create();
    }
    return object;
}

cqApplication::cqApplication() {
}

void cqApplication::setDelegate(cqApplicationDelegate::Ref delegate) {
    dat->delegate = delegate;
}

cqApplicationDelegate::Ref cqApplication::delegate() {
    return dat->delegate;
}

cqResponder::Ref cqApplication::nextResponder() {
    return dat->delegate;
}

void cqApplicationMain(cqApplicationDelegate::Ref delegate) {
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
