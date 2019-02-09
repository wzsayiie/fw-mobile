#pragma once

#include "cqviewcontroller.hh"

struct CQWindow : CQView {
CQ_CLS(CQWindow , CQView , _self_CQWindow)
    
    CQWindow();
    
    virtual void setRootViewController(CQViewController::ref controller);
    virtual CQViewController::ref rootViewController();
    
    virtual void makeKeyAndVisible();
};
