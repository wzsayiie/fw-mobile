#import "CQSubsystemManager.h"
#import "CQFoundation.h"
#import "CQSubsystemViewController.h"

@interface CQSubsystemManager ()
@property (nonatomic) UIViewController *subsystemViewController;
@end

@implementation CQSubsystemManager

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

- (void)startSubsystem {
    if (self.subsystemViewController != nil) {
        I(@"subsystem was already running");
        return;
    }
    
    self.subsystemViewController = [[CQSubsystemViewController alloc] init];
    
    UIWindow *window = UIApplication.sharedApplication.delegate.window;
    UIViewController *rootViewController = window.rootViewController;
    [rootViewController presentViewController:self.subsystemViewController
                                     animated:YES
                                   completion:nil];
}

- (void)stopSubsystem {
    if (self.subsystemViewController == nil) {
        I(@"there was no any subsystem");
        return;
    }
    
    [self.subsystemViewController dismissViewControllerAnimated:YES completion:nil];
    self.subsystemViewController = nil;
}

@end
