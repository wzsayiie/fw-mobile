#import "FloatViewController.h"

@implementation FloatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = UIColor.cyanColor;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC);
    dispatch_after(time, dispatch_get_main_queue(), ^{
        
        [UIView animateWithDuration:1.0 animations:^{
            self.view.alpha = 0;
        } completion:^(BOOL finished) {
            [self finishScene];
        }];
    });
}

@end
