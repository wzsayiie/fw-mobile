#pragma once

#include "cqview.hh"

struct CQViewController : cq_class<CQViewController, struct _self_CQViewController, CQObject> {
    
    CQViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual CQView::ref view();
    virtual void loadView();
};
