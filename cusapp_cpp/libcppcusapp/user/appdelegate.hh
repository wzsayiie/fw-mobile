#pragma once

#include "cquikit.hh"

cq_class(AppDelegate, cqApplicationDelegate) {
    
    AppDelegate();
    
    virtual void applicationDidFinishLaunching(cqWindow::ref window);
};
