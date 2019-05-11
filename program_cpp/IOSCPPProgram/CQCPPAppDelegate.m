#import "CQCPPAppDelegate.h"
#import "CQCPPViewController.h"

@interface CQCPPAppDelegate ()
@end

@implementation CQCPPAppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[CQCPPViewController alloc] init];
    [self.window makeKeyAndVisible];
    return YES;
}

@end
