#pragma once

#include "cqviewcontroller.hh"

cq_class(cqWindow, cqView) {
    
    cqWindow();
    
    virtual void setRootViewController(cqViewController::Ref controller);
    virtual cqViewController::Ref rootViewController();
    
    virtual void makeKeyAndVisible();
    
    cqResponder::Ref nextResponder() override;
    void setFrame(cqRect frame) override;
};
