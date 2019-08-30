#pragma once

#include "cqviewcontroller.hh"

_CQCOCOA_BEGIN_VERSION_NS

cq_class(cqWindow, cqView) {
    
    virtual void setRootViewController(cqViewControllerRef controller);
    virtual cqViewControllerRef rootViewController();
    
    virtual void makeKeyAndVisible();
    
    cqResponderRef nextResponder() override;
    void setFrame(cqRect frame) override;
};

_CQCOCOA_END_VERSION_NS
