#pragma once

#include "cqview.hh"

cq_class(cqViewController, cqResponder) {
    
    cqViewController();
    
    virtual void viewDidLoad();
    
    virtual cqViewRef view();
    virtual void loadView();
    
    cqResponderRef nextResponder() override;
};
