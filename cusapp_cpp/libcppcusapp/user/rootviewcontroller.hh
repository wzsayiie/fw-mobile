#pragma once

#include "cquikit.hh"

cq_class(RootViewController, _self_RootViewController, cqViewController) {

    RootViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
};
