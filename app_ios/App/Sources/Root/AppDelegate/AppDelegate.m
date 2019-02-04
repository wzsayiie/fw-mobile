#import "AppDelegate.h"
#import "KTSingletonManager.h"
#import "KTSceneNavigator.h"
#import "KTCrashListener.h"

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
    
    [KTCrashListener sharedObject];
    [KTSingletonManager sharedObject];
    
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = KTSceneNavigator.sharedObject;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
