#pragma once

#include "cqresponder.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqApplicationDelegate, cqProxy) {
    
    virtual void applicationDidFinishLaunching () {}
    virtual void applicationWillEnterForeground() {}
    virtual void applicationDidEnterBackground () {}
};

cq_class(cqApplication, cqResponder) {

    static cqApplicationRef get();
    
    virtual void setDelegate(cqApplicationDelegateRef delegate);
    virtual cqApplicationDelegateRef delegate();
    
    cqResponderRef nextResponder() override;
    
    static void main(cqApplicationDelegateRef delegate);
};

_CQAPPKIT_END_VERSION_NS
