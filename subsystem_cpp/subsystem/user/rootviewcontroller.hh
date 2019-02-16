#pragma once

#include "cquikit.hh"

struct RootViewController : cq_class<RootViewController, struct _self_RootViewController, CQViewController> {

    RootViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
};
