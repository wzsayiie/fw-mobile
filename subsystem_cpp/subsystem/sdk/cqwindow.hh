#pragma once

#include "cqviewcontroller.hh"

struct cqWindow : cq_class<cqWindow, struct _self_cqWindow, cqView> {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewController::ref controller);
    virtual cqViewController::ref rootViewController();
    
    virtual void makeKeyAndVisible();
};
