#pragma once

#include "cqcppbasis.hh"

#include "CQSUBSYSTEM_NS.hh"
_CQSUBSYSTEM_BEGIN_NS

cq_class(cqSubsystemManager, cqObject) {
    
    cqSubsystemManager();
    
    static cqSubsystemManagerRef get();
    
    virtual void startSubsystem();
    virtual void stopSubsystem();
};

_CQSUBSYSTEM_END_NS
