#pragma once

#include "cqview.hh"

cq_class(cqViewController, cqResponder) {
    
    cqViewController();
    
    virtual void viewDidLoad();
    virtual void viewDidAppear();
    virtual void viewDidDisappear();
    
    virtual cqView::Ref view();
    virtual void loadView();
    
    cqResponder::Ref nextResponder() override;
};
