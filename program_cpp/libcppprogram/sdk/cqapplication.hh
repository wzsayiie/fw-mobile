#pragma once

#include "cqresponder.hh"

cq_interface(cqApplicationDelegate, cqInterface) {

    virtual void applicationDidFinishLaunching() {}
    virtual void applicationDidBecomeActive() {}
    virtual void applicationDidEnterBackground() {}
};

cq_class(cqApplication, cqResponder) {

    static cqApplication::ref sharedApplication();
    
    cqApplication();
    
    virtual void setDelegate(cqApplicationDelegate::ref delegate);
    virtual cqApplicationDelegate::ref delegate();
};

void cqApplicationMain(cqApplicationDelegate::ref delegate);

//developers should implement _entry(), and call cqApplicationMain in it.
void _entry();
