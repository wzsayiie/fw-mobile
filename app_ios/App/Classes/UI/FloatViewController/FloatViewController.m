#import "FloatViewController.h"

@implementation FloatViewController

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    cq_dispatch_on_main(2, ^{
        
        [UIView animateWithDuration:1.0 animations:^{
            self.view.alpha = 0;
        } completion:^(BOOL finished) {
            [self finishScene];
        }];
    });
}

@end
