#pragma once

#include "cqview.hh"

cq_class(cqViewController, cqResponder) {
    
    cqViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual cqView::ref view();
    virtual void loadView();
};
