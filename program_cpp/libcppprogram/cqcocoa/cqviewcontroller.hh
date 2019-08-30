#pragma once

#include "cqview.hh"

_CQCOCOA_BEGIN_VERSION_NS

cq_class(cqViewController, cqResponder) {
    
    virtual void viewDidLoad();
    
    virtual cqViewRef view();
    virtual void loadView();
    
    cqResponderRef nextResponder() override;
};

_CQCOCOA_END_VERSION_NS
