#pragma once

#include "cqviewcontroller.hh"
#include "cqosapi.h"

cq_class(cqWindow, cqView) {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewController::ref controller);
    virtual cqViewController::ref rootViewController();
    
    virtual void setHostWindow(cq_window *window);
};
