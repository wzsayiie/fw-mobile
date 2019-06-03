#pragma once

#include "cqresponder.hh"

cq_class(cqApplicationDelegate, cqResponder) {

    cqApplicationDelegate();
    
    virtual void applicationDidFinishLaunching ();
    virtual void applicationWillEnterForeground();
    virtual void applicationDidEnterBackground ();
};

cq_class(cqApplication, cqResponder) {

    static cqApplicationRef sharedApplication();
    
    cqApplication();
    
    virtual void setDelegate(cqApplicationDelegateRef delegate);
    virtual cqApplicationDelegateRef delegate();
    
    cqResponderRef nextResponder() override;
};

void cqApplicationMain(cqApplicationDelegateRef delegate);

//developers should implement _cq_sdk_entry(), and call cqApplicationMain in it.
void _cq_sdk_entry();
