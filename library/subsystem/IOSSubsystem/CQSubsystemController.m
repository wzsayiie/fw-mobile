#import "CQSubsystemController.h"
#import "CQSubsystemManager.h"

@interface CQSubsystemController ()
@property (nonatomic) NSBundle *assetsBundle;
@property (nonatomic) IBOutlet UIButton *closeButton;
@end

@implementation CQSubsystemController

- (instancetype)init {
    NSString *name = NSStringFromClass(CQSubsystemController.class);
    return [super initWithNibName:name bundle:self.assetsBundle];
}

- (NSBundle *)assetsBundle {
    if (_assetsBundle == nil) {
        NSString *path = [NSBundle.mainBundle pathForResource:@"Resource" ofType:@"bundle"];
        _assetsBundle = [NSBundle bundleWithPath:path];
    }
    return _assetsBundle;
}

- (NSString *)L:(NSString *)name {
    return NSLocalizedStringFromTableInBundle(name, @"L", self.assetsBundle, nil);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSString *title = [self L:@"close"];
    [self.closeButton setTitle:title forState:UIControlStateNormal];
}

- (IBAction)handleCloseButtonTouch:(UIButton *)sender {
    [self removeFromUI];
}

- (void)removeFromUI {
    [CQSubsystemManager.sharedObject stopSubsystem];
}

@end
