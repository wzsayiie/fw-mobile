#include "cqapplication.hh"
#include "cqwindow.h"

cq_member(cqApplicationDelegate) {
};

cqApplicationDelegate::cqApplicationDelegate() {
}

void cqApplicationDelegate::applicationDidFinishLaunching () {}
void cqApplicationDelegate::applicationWillEnterForeground() {}
void cqApplicationDelegate::applicationDidEnterBackground () {}

cq_member(cqApplication) {
    cqApplicationDelegateRef delegate;
};

cqApplicationRef cqApplication::get() {
    CQ_SYNCHRONIZE
    
    static cqApplicationRef object;
    if (object == nullptr) {
        object = cqApplication::create();
    }
    return object;
}

cqApplication::cqApplication() {
}

void cqApplication::setDelegate(cqApplicationDelegateRef delegate) {
    dat->delegate = delegate;
}

cqApplicationDelegateRef cqApplication::delegate() {
    return dat->delegate;
}

cqResponderRef cqApplication::nextResponder() {
    return dat->delegate;
}

void cqApplicationMain(cqApplicationDelegateRef delegate) {
    if (delegate == nullptr) {
        return;
    }
    
    cqApplication::get()->setDelegate(delegate);
    if (delegate != nullptr) {
        delegate->applicationDidFinishLaunching();
    }
}
