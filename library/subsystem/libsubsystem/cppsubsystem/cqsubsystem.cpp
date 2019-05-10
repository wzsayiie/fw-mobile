#include "cqsubsystem.hh"
#include "cqsubsystemarche.h"

cq_member(cqSubsystemManager) {
};

cqSubsystemManager::cqSubsystemManager() {
}

cqSubsystemManager::ref cqSubsystemManager::get() {
    static cqSubsystemManager::ref object;
    if (object == nullptr) {
        object = cqSubsystemManager::create();
    }
    return object;
}

bool cqSubsystemManager::startSubsystem(cqString::ref name) {
    return cq_subsystem_start(name->data());
}

void cqSubsystemManager::stopSubsystem(cqString::ref name) {
    cq_subsystem_stop(name->data());
}
