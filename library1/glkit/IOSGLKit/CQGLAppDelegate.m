#import "CQGLAppDelegate.h"
#import "CQGLViewController.h"

@implementation CQGLAppDelegate

- (BOOL) /* ...... */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CQGLViewController *controller = [[CQGLViewController alloc] init];
    controller.coreAppEntry = [self coreAppEntry];
    
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = controller;
    [self.window makeKeyAndVisible];
    
    return YES;
}

- (void (*)(void))coreAppEntry {
    return NULL;
}

@end
