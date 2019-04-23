#import "CQDefaultSubsystemController.h"

@interface CQDefaultSubsystemController ()
@end

@implementation CQDefaultSubsystemController

- (instancetype)init {
    return [super initWithNibName:@"CQDefaultSubsystemController" bundle:self.assetsBundle];
}

- (NSBundle *)assetsBundle {
    NSString *bundlePath = [NSBundle.mainBundle pathForResource:@"Resource" ofType:@"bundle"];
    NSBundle *bundle = [NSBundle bundleWithPath:bundlePath];
    return bundle;
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (IBAction)handleCloseButtonTouch:(UIButton *)sender {
    [self removeFromUI];
}

@end
