#include "cqsubsystem.hh"
#include "cqsubsystemintf.h"

cq_member(cqSubsystemManager) {
};

cqSubsystemManagerRef cqSubsystemManager::get() {
    return cqStaticObject<cqSubsystemManager>();
}

void cqSubsystemManager::startSubsystem() {
    cq_subsystem_start();
}

void cqSubsystemManager::stopSubsystem() {
    cq_subsystem_stop();
}
