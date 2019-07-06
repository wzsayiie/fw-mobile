#pragma once

#include "cqresponder.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

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

_CQUIKIT_END_NS
