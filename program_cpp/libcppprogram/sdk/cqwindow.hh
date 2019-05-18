#pragma once

#include "cqviewcontroller.hh"

cq_class(cqWindow, cqView) {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewControllerRef controller);
    virtual cqViewControllerRef rootViewController();
    
    virtual void makeKeyAndVisible();
    
    cqResponderRef nextResponder() override;
    void setFrame(cqRect frame) override;
};
