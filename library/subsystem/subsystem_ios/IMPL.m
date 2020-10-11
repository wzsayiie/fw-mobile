#import "CQSubsystem.h"
#import "cqsubsystemintf.h"

void cq_subsystem_start() {
    return [CQSubsystemManager.sharedObject startSubsystem];
}

void cq_subsystem_stop() {
    [CQSubsystemManager.sharedObject stopSubsystem];
}
