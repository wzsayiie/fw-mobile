#pragma once

#include "cqview.hh"

struct CQViewController : CQObject {
CQ_CLS(CQViewController , CQObject , _self_CQViewController)
    
    CQViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual CQView::ref view();
    virtual void loadView();
};
