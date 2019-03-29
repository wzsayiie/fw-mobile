#import "CQCPPViewController.h"
#import "cqhostapi.h"

@interface CQCPPViewController ()
@end

@implementation CQCPPViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    I(@"iOS Host: ViewController viewDidLoad");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"iOS Host: ViewController viewDidAppear");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"iOS Host: ViewController viewDidDisappear");
}

@end
