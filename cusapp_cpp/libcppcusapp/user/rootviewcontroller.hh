#pragma once

#include "cquikit.hh"

cq_class(RootViewController, cqViewController) {

    RootViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
};
