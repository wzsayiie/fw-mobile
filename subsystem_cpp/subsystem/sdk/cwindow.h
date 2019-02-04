#pragma once

#include "cviewcontroller.h"

struct CWindow : CView {
C_CLAS(CWindow , CView , _self_CWindow)
    
    CWindow();
    
    virtual void setRootViewController(CViewController::ref controller);
    virtual CViewController::ref rootViewController();
    
    virtual void makeKeyAndVisible();
};
