#import "GameAppDelegate.h"

void _cs_game_entry(void);

@implementation GameAppDelegate

- (BOOL)application:(UIApplication *)a didFinishLaunchingWithOptions:(NSDictionary *)o {
    [super application:a didFinishLaunchingWithOptions:o];
    _cs_game_entry();
    return YES;
}

@end
