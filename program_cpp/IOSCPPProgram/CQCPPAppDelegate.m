#import "CQCPPAppDelegate.h"
#import "CQCPPViewController.h"
#import "cqosapi.h"

@implementation CQCPPAppDelegate

+ (CQCPPAppDelegate *)sharedObject {
    return (CQCPPAppDelegate *)UIApplication.sharedApplication.delegate;
}
static int64_t create_window(void) {
    return [CQCPPAppDelegate.sharedObject createWindow];
}
static void show_window(int64_t wid) {
    return [CQCPPAppDelegate.sharedObject showWindow:wid];
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
    _cq_notify_app_startup();
    
    return YES;
}

- (int64_t)createWindow {
    
    //only one window can be created on ios
    if (self.window != nil) {
        return 0;
    }
    
    CQCPPViewController *controller = [[CQCPPViewController alloc] init];
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = controller;
    return controller.wid;
}

- (void)showWindow:(int64_t)wid {
    if (wid == ((CQCPPViewController *)self.window.rootViewController).wid) {
        [self.window makeKeyAndVisible];
    }
}

@end
