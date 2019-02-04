#pragma once

#include "cahead.h"

struct CApplicationDelegate : CObject {
C_INTF(CApplicationDelegate)
    
    virtual void applicationDidFinishLaunching() {}
    virtual void applicationDidBecomeActive() {}
    virtual void applicationDidEnterBackground() {}
};

struct CApplication : CObject {
C_CLAS(CApplication , CObject, _self_CApplication)
    
    static CApplication::ref sharedApplication();
    
    CApplication();
    
    virtual void setDelegate(CApplicationDelegate::ref delegate);
    virtual CApplicationDelegate::ref delegate();
};

void CApplicationMain(CApplicationDelegate::ref delegate);
