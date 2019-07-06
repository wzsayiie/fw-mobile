#pragma once

#include "cqview.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

cq_class(cqViewController, cqResponder) {
    
    virtual void viewDidLoad();
    
    virtual cqViewRef view();
    virtual void loadView();
    
    cqResponderRef nextResponder() override;
};

_CQUIKIT_END_NS
