#pragma once

#include "cqcppbasis.hh"

cq_class(cqSubsystemManager, cqObject) {
    
    cqSubsystemManager();
    
    static cqSubsystemManager::ref get();
    
    virtual bool startSubsystem(const std::string &name);
    virtual void stopSubsystem(const std::string &name);
};
