#include "cqsubsystem.hh"
#include "cqsubsystemarche.h"

cq_member(cqSubsystemManager) {
};

cqSubsystemManager::cqSubsystemManager() {
}

cqSubsystemManagerRef cqSubsystemManager::get() {
    CQ_SYNCHRONIZE
    
    static cqSubsystemManagerRef object;
    if (object == nullptr) {
        object = cqSubsystemManager::create();
    }
    return object;
}

void cqSubsystemManager::startSubsystem() {
    cq_subsystem_start();
}

void cqSubsystemManager::stopSubsystem() {
    cq_subsystem_stop();
}
