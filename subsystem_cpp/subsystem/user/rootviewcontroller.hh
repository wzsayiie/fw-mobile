#pragma once

#include "cquikit.hh"

struct RootViewController : CQViewController {
CQ_CLS(RootViewController , CQViewController , _self_RootViewController);
    
    RootViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
};
