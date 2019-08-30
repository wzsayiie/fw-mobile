#pragma once

#include "cqresponder.hh"

_CQCOCOA_BEGIN_VERSION_NS

cq_class(cqApplicationDelegate, cqResponder) {
    
    virtual void applicationDidFinishLaunching ();
    virtual void applicationWillEnterForeground();
    virtual void applicationDidEnterBackground ();
};

cq_class(cqApplication, cqResponder) {

    static cqApplicationRef get();
    
    virtual void setDelegate(cqApplicationDelegateRef delegate);
    virtual cqApplicationDelegateRef delegate();
    
    cqResponderRef nextResponder() override;
    
    static void main(cqApplicationDelegateRef delegate);
};

_CQCOCOA_END_VERSION_NS
