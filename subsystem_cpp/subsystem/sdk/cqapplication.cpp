#include "cqapplication.hh"
#include "cqhost_p.hh"

struct _self_CQApplication {
    CQApplicationDelegate::ref delegate;
};

CQApplication::ref CQApplication::sharedApplication() {
    static CQApplication::ref object;
    if (object == nullptr) {
        object = CQApplication::create();
    }
    return object;
}

static void onAppCreate(shared_ptr<_self_CQApplication> self) {
    if (self->delegate != nullptr) {
        self->delegate->applicationDidFinishLaunching();
    }
}

static void onUIAppear(shared_ptr<_self_CQApplication> self) {
    if (self->delegate != nullptr) {
        self->delegate->applicationDidBecomeActive();
    }
}

static void onUIDisappear(shared_ptr<_self_CQApplication> self) {
    if (self->delegate != nullptr) {
        self->delegate->applicationDidEnterBackground();
    }
}

CQApplication::CQApplication() {
    C_INIT(self);
    
    CQHostAddListener(CQHostEventAppCreate  , bind(onAppCreate  , self));
    CQHostAddListener(CQHostEventUIAppear   , bind(onUIAppear   , self));
    CQHostAddListener(CQHostEventUIDisappear, bind(onUIDisappear, self));
}

void CQApplication::setDelegate(CQApplicationDelegate::ref delegate) {
    self->delegate = delegate;
}

CQApplicationDelegate::ref CQApplication::delegate() {
    return self->delegate;
}

void CQApplicationMain(CQApplicationDelegate::ref delegate) {
    CQApplication::sharedApplication()->setDelegate(delegate);
}
