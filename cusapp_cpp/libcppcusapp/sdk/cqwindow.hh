#pragma once

#include "cqviewcontroller.hh"
#include "cqhostapi.h"

cq_class(cqWindow, _self_cqWindow, cqView) {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewController::ref controller);
    virtual cqViewController::ref rootViewController();
    
    virtual void setHostWindow(cq_window *window);
};
