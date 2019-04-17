#pragma once

#include "cquikit.hh"

struct AppDelegate : cq_class<AppDelegate, struct _self_AppDelegate, cqApplicationDelegate> {
    
    AppDelegate();
    
    virtual void applicationDidFinishLaunching(cqWindow::ref window);
};
