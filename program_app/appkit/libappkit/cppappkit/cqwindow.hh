#pragma once

#include "cqviewcontroller.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqWindow, cqView) {
    
    virtual void setRootViewController(cqViewControllerRef controller);
    virtual cqViewControllerRef rootViewController();
    
    virtual void makeKeyAndVisible();
    
    cqResponderRef nextResponder() override;
    void setFrame(cqRect frame) override;
};

_CQAPPKIT_END_VERSION_NS
