#include "cqapplication.hh"

cq_member(cqApplicationDelegate) {
};

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
    cqApplicationDelegateRef delegate = dat->delegate;
    if (delegate != nullptr) {
        cqObjectRef core = delegate->core();
        if (core->isKindOfClass(cqResponder::clazz())) {
            return cqObject::cast<cqResponder>(core);
        }
    }
    return nullptr;
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
