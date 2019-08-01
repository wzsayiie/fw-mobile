#pragma once

#include "cqcppbasis.hh"

#include "_CQSUBSYSTEM_VERSION.h"
_CQSUBSYSTEM_BEGIN_VERSION_NS

cq_class(cqSubsystemManager, cqObject) {
    
    static cqSubsystemManagerRef get();
    
    virtual void startSubsystem();
    virtual void stopSubsystem();
};

_CQSUBSYSTEM_END_VERSION_NS
