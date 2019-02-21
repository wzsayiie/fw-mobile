#pragma once

#include "cqviewcontroller.hh"

struct CQWindow : cq_class<CQWindow, struct _self_CQWindow, CQView> {
    
    CQWindow();
    
    virtual void setRootViewController(CQViewController::ref controller);
    virtual CQViewController::ref rootViewController();
    
    virtual void makeKeyAndVisible();
};
