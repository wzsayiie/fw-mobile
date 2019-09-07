#import "AppAppDelegate.h"

void _cq_app_entry(void);

@implementation AppAppDelegate

- (BOOL)application:(UIApplication *)a didFinishLaunchingWithOptions:(NSDictionary *)o {
    [super application:a didFinishLaunchingWithOptions:o];
    _cq_app_entry();
    return YES;
}

@end
