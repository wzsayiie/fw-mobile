#import "FloatViewController.h"

@implementation FloatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.alpha = 0;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    //gradually appear.
    [UIView animateWithDuration:1 animations:^{
        self.view.alpha = 1;
    } completion:nil];
    
    //gradually disappear.
    cq_dispatch_on_main(2, ^{
        [UIView animateWithDuration:1 animations:^{
            self.view.alpha = 0;
        } completion:nil];
    });
    
    //remove.
    cq_dispatch_on_main(3, ^{
        [self finishScene];
    });
}

@end
