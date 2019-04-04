#import "CQCPPAppDelegate.h"
#import "CQCPPViewController.h"
#import "CQLog.h"

@interface CQCPPAppDelegate ()
@end

@implementation CQCPPAppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    I(@"host: finish launching enter");
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[CQCPPViewController alloc] init];
    [self.window makeKeyAndVisible];
    I(@"host: finish launching exit");
        
    return YES;
}

@end
