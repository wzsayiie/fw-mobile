#pragma once

#include "cquikit.hh"

struct AppDelegate : cq_class<AppDelegate, struct _self_AppDelegate, CQApplicationDelegate> {
    
    AppDelegate();
    
    virtual void applicationDidFinishLaunching();
};
