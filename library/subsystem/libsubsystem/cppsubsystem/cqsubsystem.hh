#pragma once

#include "cqcppbasis.hh"

cq_class(cqSubsystemManager, _self_cqSubsystemManager, cqObject) {
    
    cqSubsystemManager();
    
    static cqSubsystemManager::ref sharedObject();
    
    virtual bool startSubsystem(const string &name);
    virtual void stopSubsystem(const string &name);
};
