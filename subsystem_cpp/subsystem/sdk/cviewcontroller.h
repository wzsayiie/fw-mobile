#pragma once

#include "cview.h"

struct CViewController : CObject {
C_CLAS(CViewController , CObject , _self_CViewController)
    
    CViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual CView::ref view();
    virtual void loadView();
};
