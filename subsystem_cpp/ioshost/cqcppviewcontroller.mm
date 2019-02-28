#import "cqcppviewcontroller.h"
#import "cqhost_p.hh"

extern "C" void _main();

@interface CQCPPViewController ()
@end

@implementation CQCPPViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    
    _main();
    CQHostOnEvent(CQHostEventAppCreate);
    CQHostOnEvent(CQHostEventUILoad);
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    CQHostOnEvent(CQHostEventUIAppear);
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    CQHostOnEvent(CQHostEventUIDisappear);
}

@end
