#import "AppDelegate.h"
#import "KTSingletonManager.h"
#import "KTSceneNavigator.h"
#import "KTCrashListener.h"

@implementation AppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    I(@"app launching {");
    I(@"  device name: %@", UIDevice.currentDevice.name);
    I(@"  hardware type: %@", UIDevice.currentDevice.hardwareType);
    I(@"  system version: %@", UIDevice.currentDevice.systemVersion);
    I(@"  vendor ID: %@", UIDevice.currentDevice.identifierForVendor);
    I(@"}");
    
    [KTCrashListener sharedObject];
    [KTSingletonManager sharedObject];
    
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = KTSceneNavigator.sharedObject;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end

int main(int argc, char *argv[]) {
    return UIApplicationMain(argc, argv, nil, @"AppDelegate");
}
