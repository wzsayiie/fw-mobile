#pragma once

#include "cqconvention.hh"

struct CQApplicationDelegate : cq_interface<CQApplicationDelegate, cqInterface> {
    
    virtual void applicationDidFinishLaunching() {}
    virtual void applicationDidBecomeActive() {}
    virtual void applicationDidEnterBackground() {}
};

struct CQApplication : cq_class<CQApplication, struct _self_CQApplication, cqObject> {
    
    static CQApplication::ref sharedApplication();
    
    CQApplication();
    
    virtual void setDelegate(CQApplicationDelegate::ref delegate);
    virtual CQApplicationDelegate::ref delegate();
};

void CQApplicationMain(CQApplicationDelegate::ref delegate);
