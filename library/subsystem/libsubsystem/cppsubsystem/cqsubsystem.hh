#pragma once

#include "cqcppbasis.hh"

cq_class(cqSubsystemManager, cqObject) {
    
    cqSubsystemManager();
    
    static cqSubsystemManagerRef get();
    
    virtual void startSubsystem();
    virtual void stopSubsystem();
};
