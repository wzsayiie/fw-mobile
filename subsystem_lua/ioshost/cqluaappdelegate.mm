#import "cqluaappdelegate.h"
#import "cqluaviewcontroller.h"

@interface CQLuaAppDelegate ()
@end

@implementation CQLuaAppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    I(@"iOS Host: Application didFinishLaunching");
    
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[CQLuaViewController alloc] init];
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
