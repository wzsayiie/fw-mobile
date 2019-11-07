#import "AppAppDelegate.h"

void _cq_app_entry(void);

@implementation AppAppDelegate

- (void (*)(void))coreAppEntry {
    return _cq_app_entry;
}

@end
