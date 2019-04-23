#import "CQSubsystem.h"
#import "cqsubsystemarche.h"

bool cq_subsystem_start(const char *name) {
    return [CQSubsystemManager.sharedObject startSubsystem:@(name)];
}

void cq_subsystem_stop(const char *name) {
    [CQSubsystemManager.sharedObject stopSubsystem:@(name)];
}
