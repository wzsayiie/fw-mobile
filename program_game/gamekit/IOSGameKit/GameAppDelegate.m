#import "GameAppDelegate.h"

void _cq_lua_entry(void);

@implementation GameAppDelegate

- (BOOL)application:(UIApplication *)a didFinishLaunchingWithOptions:(NSDictionary *)o {
    [super application:a didFinishLaunchingWithOptions:o];
    _cq_lua_entry();
    return YES;
}

@end
