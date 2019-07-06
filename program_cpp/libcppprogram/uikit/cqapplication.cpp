#include "cqapplication.hh"
#include "cqwindow.h"

cq_member(cqApplicationDelegate) {
};

void cqApplicationDelegate::applicationDidFinishLaunching () {}
void cqApplicationDelegate::applicationWillEnterForeground() {}
void cqApplicationDelegate::applicationDidEnterBackground () {}

cq_member(cqApplication) {
    cqApplicationDelegateRef delegate;
};

cqApplicationRef cqApplication::get() {
    return cqStaticObject<cqApplication>();
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

void cqApplication::main(cqApplicationDelegateRef delegate) {
    if (delegate == nullptr) {
        return;
    }
    
    cqApplication::get()->setDelegate(delegate);
    if (delegate != nullptr) {
        delegate->applicationDidFinishLaunching();
    }
}
