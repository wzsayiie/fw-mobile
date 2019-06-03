#import "CQHostAppDelegate.h"
#import "CQHostViewController.h"
#import "cqhostapi.h"

@implementation CQHostAppDelegate

+ (CQHostAppDelegate *)sharedObject {
    return (CQHostAppDelegate *)UIApplication.sharedApplication.delegate;
}
static int64_t create_window(void) {
    return [CQHostAppDelegate.sharedObject createWindow];
}
static void show_window(int64_t wid) {
    return [CQHostAppDelegate.sharedObject showWindow:wid];
}

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //enable interfaces
    _cq_interfaces interfaces;
    interfaces.create_window = create_window;
    interfaces.show_window = show_window;
    _cq_install_interfaces(&interfaces);
    
    //entry
    _cq_notify_app_launch();
    
    return YES;
}

- (int64_t)createWindow {
    
    //only one window can be created on ios
    if (self.window != nil) {
        return 0;
    }
    
    CQHostViewController *controller = [[CQHostViewController alloc] init];
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = controller;
    return controller.wid;
}

- (void)showWindow:(int64_t)wid {
    if (wid == ((CQHostViewController *)self.window.rootViewController).wid) {
        [self.window makeKeyAndVisible];
    }
}

@end
