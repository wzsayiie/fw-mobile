#pragma once

#include "cqviewcontroller.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

cq_class(cqWindow, cqView) {
    
    virtual void setRootViewController(cqViewControllerRef controller);
    virtual cqViewControllerRef rootViewController();
    
    virtual void makeKeyAndVisible();
    
    cqResponderRef nextResponder() override;
    void setFrame(cqRect frame) override;
};

_CQUIKIT_END_NS
