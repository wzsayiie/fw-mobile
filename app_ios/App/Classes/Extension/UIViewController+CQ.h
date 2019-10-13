//

@interface UIViewController (CQ)

//NOTE: $view must be self.view or it's subview.
- (void)safeView:(UIView *)view addChildController:(UIViewController *)controller;

- (void)safeAddChildController:(UIViewController *)controller;
- (void)safeRemoveFromParentController;

@end
