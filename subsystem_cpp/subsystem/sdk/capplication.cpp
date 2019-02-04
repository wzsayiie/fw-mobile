#include "capplication.h"
#include "chost_p.h"

struct _self_CApplication {
    CApplicationDelegate::ref delegate;
};

static void onAppCreate(shared_ptr<_self_CApplication> self) {
    if (self->delegate != nullptr) {
        self->delegate->applicationDidFinishLaunching();
    }
}

static void onUIAppear(shared_ptr<_self_CApplication> self) {
    if (self->delegate != nullptr) {
        self->delegate->applicationDidBecomeActive();
    }
}

static void onUIDisappear(shared_ptr<_self_CApplication> self) {
    if (self->delegate != nullptr) {
        self->delegate->applicationDidEnterBackground();
    }
}

CApplication::ref CApplication::sharedApplication() {
    static CApplication::ref object;
    if (object == nullptr) {
        object = CApplication::create();
    }
    return object;
}

CApplication::CApplication() {
    C_INIT(self);
    
    CHostAddListener(CHostEventAppCreate  , bind(onAppCreate  , self));
    CHostAddListener(CHostEventUIAppear   , bind(onUIAppear   , self));
    CHostAddListener(CHostEventUIDisappear, bind(onUIDisappear, self));
}

void CApplication::setDelegate(CApplicationDelegate::ref delegate) {
    self->delegate = delegate;
}

CApplicationDelegate::ref CApplication::delegate() {
    return self->delegate;
}

void CApplicationMain(CApplicationDelegate::ref delegate) {
    CApplication::sharedApplication()->setDelegate(delegate);
}
