#include "cqsubsystem.hh"
#include "cqsubsystemarche.h"

cq_member(cqSubsystemManager) {
};

cqSubsystemManager::cqSubsystemManager() {
}

cqSubsystemManagerRef cqSubsystemManager::get() {
    static cqSubsystemManagerRef object;
    if (object == nullptr) {
        object = cqSubsystemManager::create();
    }
    return object;
}

bool cqSubsystemManager::startSubsystem(const std::string &name) {
    return cq_subsystem_start(name.data());
}

void cqSubsystemManager::stopSubsystem(const std::string &name) {
    cq_subsystem_stop(name.data());
}
