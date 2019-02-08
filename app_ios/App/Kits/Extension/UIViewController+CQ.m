#import "UIViewController+CQ.h"

@implementation UIViewController (CQ)

- (void)addFillingSubviewWithController:(UIViewController *)childController {
    [self addChildViewController:childController];
    [self.view addFillingSubview:childController.view];
    [childController didMoveToParentViewController:self];
}

- (void)removeFillingSubviewAndController {
    [self willMoveToParentViewController:nil];
    [self.view removeFromSuperview];
    [self removeFromParentViewController];
}

@end
