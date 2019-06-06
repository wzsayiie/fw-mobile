#import "CPPHostAppDelegate.h"

void _cq_cpp_entry(void);

@implementation CPPHostAppDelegate

- (BOOL)application:(UIApplication *)a didFinishLaunchingWithOptions:(NSDictionary *)o {
    [super application:a didFinishLaunchingWithOptions:o];
    _cq_cpp_entry();
    return YES;
}

@end
