#pragma once

#include "cuikit.h"

struct RootViewController : CViewController {
C_CLAS(RootViewController , CViewController , _self_RootViewController);
    
    RootViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
};
