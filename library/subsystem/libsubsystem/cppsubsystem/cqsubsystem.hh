#pragma once

#include "cqcppbasis.hh"

struct cqSubsystemManager : cq_class<cqSubsystemManager, struct _self_cqSubsystemManager, cqObject> {
    
    cqSubsystemManager();
    
    static cqSubsystemManager::ref sharedObject();
    
    virtual bool startSubsystem(const string &name);
    virtual void stopSubsystem(const string &name);
};
