#import "CQCPPAppDelegate.h"
#import "CQCPPViewController.h"

@interface CQCPPAppDelegate ()
@end

@implementation CQCPPAppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    I(@"iOS Host: didFinishLaunching enter");
    {
        self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
        self.window.rootViewController = [[CQCPPViewController alloc] init];
        [self.window makeKeyAndVisible];
    }
    I(@"iOS Host: didFinishLaunching exit");
    return YES;
}

@end
