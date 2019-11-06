#import "CQGLAppDelegate.h"
#import "CQGLViewController.h"
#import "cqwnd.h"

@implementation CQGLAppDelegate

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT(self);
}

static float wnd_scale(void) {
    return [CQGLAppDelegate.sharedObject windowScale];
}
static int64_t new_wnd(void) {
    return [CQGLAppDelegate.sharedObject createWindow];
}
static void show_wnd(int64_t wid) {
    return [CQGLAppDelegate.sharedObject showWindow:wid];
}

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    struct _cq_wndport port = {NULL}; {
        port.wnd_scale = wnd_scale;
        port.new_wnd   = new_wnd;
        port.show_wnd  = show_wnd;
    }
    _cq_init_wndport(&port);
    
    //NOTE: call entry function here.
    
    return YES;
}

- (float)windowScale {
    return UIScreen.mainScreen.scale;
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
