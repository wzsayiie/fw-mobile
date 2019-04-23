#pragma once

#include "cqwindow.hh"

struct cqApplication;

cq_interface(cqApplicationDelegate, cqInterface) {
    
    virtual void applicationDidFinishLaunching(cqWindow::ref window) {}
    virtual void applicationDidBecomeActive() {}
    virtual void applicationDidEnterBackground() {}
};

cq_class(cqApplication, _self_cqApplication, cqObject) {
    
    static cqApplication::ref sharedApplication();
    
    cqApplication();
    
    virtual void setDelegate(cqApplicationDelegate::ref delegate);
    virtual cqApplicationDelegate::ref delegate();
    
    virtual void setWindow(cqWindow::ref window);
    virtual cqWindow::ref window();
};

void cqApplicationMain(cqApplicationDelegate::ref delegate);

//developers should implement _entry(), and call cqApplicationMain in it.
void _entry();
