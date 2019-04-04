#pragma once

#include "cqviewcontroller.hh"
#include "cqhostapi.h"

struct cqWindow : cq_class<cqWindow, struct _self_cqWindow, cqView> {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewController::ref controller);
    virtual cqViewController::ref rootViewController();
    
    virtual void setHostWindow(cq_window *window);
};
