#include "cqapplication.hh"

struct _self_cqApplication {
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
    cqApplication::sharedApplication()->setDelegate(delegate);
}
