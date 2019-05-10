#pragma once

#include "cqcppbasis.hh"

cq_class(cqSubsystemManager, cqObject) {
    
    cqSubsystemManager();
    
    static cqSubsystemManager::ref get();
    
    virtual bool startSubsystem(cqString::ref name);
    virtual void stopSubsystem(cqString::ref name);
};
