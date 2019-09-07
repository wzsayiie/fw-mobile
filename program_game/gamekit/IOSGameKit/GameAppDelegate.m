#import "GameAppDelegate.h"

void _cq_game_entry(void);

@implementation GameAppDelegate

- (BOOL)application:(UIApplication *)a didFinishLaunchingWithOptions:(NSDictionary *)o {
    [super application:a didFinishLaunchingWithOptions:o];
    _cq_game_entry();
    return YES;
}

@end
