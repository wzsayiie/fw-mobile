#import "AppDelegate.h"
#import "CQSceneNavigator.h"
#import "CQCrashListener.h"

@implementation AppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    I(@"app launching {");
    I(@"  hardware   : %@", UIDevice.currentDevice.hardwareType);
    I(@"  os version : %@", UIDevice.currentDevice.systemVersion);
    I(@"  bundle id  : %@", NSBundle.mainBundle.bundleIdentifier);
    I(@"  app version: %@", NSBundle.mainBundle.appVersion);
    I(@"  vendor id  : %@", UIDevice.currentDevice.identifierForVendor);
    I(@"}");
    
    [CQCrashListener sharedObject];
    
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = CQSceneNavigator.sharedObject;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
