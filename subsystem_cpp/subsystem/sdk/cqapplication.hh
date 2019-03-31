#pragma once

#include "cqconvention.hh"

struct cqApplicationDelegate : cq_interface<cqApplicationDelegate, cqInterface> {
    
    virtual void applicationDidFinishLaunching() {}
    virtual void applicationDidBecomeActive() {}
    virtual void applicationDidEnterBackground() {}
};

struct cqApplication : cq_class<cqApplication, struct _self_cqApplication, cqObject> {
    
    static cqApplication::ref sharedApplication();
    
    cqApplication();
    
    virtual void setDelegate(cqApplicationDelegate::ref delegate);
    virtual cqApplicationDelegate::ref delegate();
};

void cqApplicationMain(cqApplicationDelegate::ref delegate);
