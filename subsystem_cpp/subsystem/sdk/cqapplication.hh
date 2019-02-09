#pragma once

#include "cqobject.hh"

struct CQApplicationDelegate : CQObject {
CQ_ITF(CQApplicationDelegate)
    
    virtual void applicationDidFinishLaunching() {}
    virtual void applicationDidBecomeActive() {}
    virtual void applicationDidEnterBackground() {}
};

struct CQApplication : CQObject {
CQ_CLS(CQApplication , CQObject, _self_CQApplication)
    
    static CQApplication::ref sharedApplication();
    
    CQApplication();
    
    virtual void setDelegate(CQApplicationDelegate::ref delegate);
    virtual CQApplicationDelegate::ref delegate();
};

void CQApplicationMain(CQApplicationDelegate::ref delegate);
