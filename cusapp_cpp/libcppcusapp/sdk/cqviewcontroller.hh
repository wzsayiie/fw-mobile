#pragma once

#include "cqview.hh"

struct cqViewController : cq_class<cqViewController, struct _self_cqViewController, cqObject> {
    
    cqViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual cqView::ref view();
    virtual void loadView();
};
