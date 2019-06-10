#import "CQSubsystemViewController.h"
#import "CQSubsystemManager.h"

@interface CQSubsystemViewController ()
@end

@implementation CQSubsystemViewController

- (instancetype)init {
    return [super initWithNibName:@"CQSubsystemViewController" bundle:self.assetsBundle];
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

- (void)removeFromUI {
    [CQSubsystemManager.sharedObject stopSubsystem];
}

@end
