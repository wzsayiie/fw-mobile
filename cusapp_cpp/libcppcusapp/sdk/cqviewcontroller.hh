#pragma once

#include "cqview.hh"

cq_class(cqViewController, _self_cqViewController, cqResponder) {
    
    cqViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual cqView::ref view();
    virtual void loadView();
};
