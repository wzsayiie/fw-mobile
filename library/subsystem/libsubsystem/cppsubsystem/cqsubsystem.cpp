#include "cqsubsystem.hh"
#include "cqsubsystemarche.h"

cq_member(cqSubsystemManager) {
};

cqSubsystemManager::cqSubsystemManager() {
}

cqSubsystemManagerRef cqSubsystemManager::get() {
    return cqStaticObject<cqSubsystemManager>();
}

void cqSubsystemManager::startSubsystem() {
    cq_subsystem_start();
}

void cqSubsystemManager::stopSubsystem() {
    cq_subsystem_stop();
}
