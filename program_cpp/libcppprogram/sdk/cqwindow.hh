#pragma once

#include "cqviewcontroller.hh"

cq_class(cqWindow, cqView) {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewController::ref controller);
    virtual cqViewController::ref rootViewController();
    
    virtual void makeKeyAndVisible();
};
