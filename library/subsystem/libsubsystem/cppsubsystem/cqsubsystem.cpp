#include "cqsubsystem.hh"
#include "cqsubsystemarche.h"

struct _self_cqSubsystemManager {
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

bool cqSubsystemManager::startSubsystem(const string &name) {
    return cq_subsystem_start(name.data());
}

void cqSubsystemManager::stopSubsystem(const string &name) {
    cq_subsystem_stop(name.data());
}
