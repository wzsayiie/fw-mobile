#pragma once

#include "cqresponder.hh"

cq_class(cqApplicationDelegate, cqResponder) {

    cqApplicationDelegate();
    
    virtual void applicationDidFinishLaunching();
    virtual void applicationDidBecomeActive();
    virtual void applicationDidEnterBackground();
};

cq_class(cqApplication, cqResponder) {

    static cqApplication::Ref sharedApplication();
    
    cqApplication();
    
    virtual void setDelegate(cqApplicationDelegate::Ref delegate);
    virtual cqApplicationDelegate::Ref delegate();
    
    cqResponder::Ref nextResponder() override;
};

void cqApplicationMain(cqApplicationDelegate::Ref delegate);

//developers should implement _entry(), and call cqApplicationMain in it.
void _entry();
