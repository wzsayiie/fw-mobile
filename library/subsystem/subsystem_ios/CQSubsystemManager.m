#import "CQSubsystemManager.h"
#import "CQFoundation.h"
#import "CQSubsystemController.h"

@interface CQSubsystemManager ()
@property (nonatomic) UIViewController *subsystemController;
@end

@implementation CQSubsystemManager

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT_OF_SELF();
}

- (void)startSubsystem {
    if (self.subsystemController != nil) {
        I(@"subsystem was already running");
        return;
    }
    
    self.subsystemController = [[CQSubsystemController alloc] init];
    
    UIWindow *window = UIApplication.sharedApplication.delegate.window;
    UIViewController *rootViewController = window.rootViewController;
    [rootViewController presentViewController:self.subsystemController
                                     animated:YES
                                   completion:nil];
}

- (void)stopSubsystem {
    if (self.subsystemController == nil) {
        I(@"there was no any subsystem");
        return;
    }
    
    [self.subsystemController dismissViewControllerAnimated:YES completion:nil];
    self.subsystemController = nil;
}

@end
