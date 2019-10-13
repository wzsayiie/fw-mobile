#import "UIViewController+CQ.h"

@implementation UIViewController (CQ)

- (void)safeView:(UIView *)view addChildController:(UIViewController *)controller {
    if (view != nil && controller != nil) {
        [self addChildViewController:controller];
        [view addFillingSubview:controller.view];
        [controller didMoveToParentViewController:self];
    }
}

- (void)safeAddChildController:(UIViewController *)controller {
    if (controller != nil) {
        [self safeView:self.view addChildController:controller];
    }
}

- (void)safeRemoveFromParentController {
    [self willMoveToParentViewController:nil];
    [self.view removeFromSuperview];
    [self removeFromParentViewController];
}

@end
