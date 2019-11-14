#import "GameAppDelegate.h"

void _cs_game_entry(void);

@implementation GameAppDelegate

- (void (*)(void))coreAppEntry {
    return _cs_game_entry;
}

@end
