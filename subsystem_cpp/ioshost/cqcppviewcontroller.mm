#import "cqcppviewcontroller.h"
#import "cqhost_p.hh"

extern "C" void _main();

@interface CQCPPViewController ()
@end

@implementation CQCPPViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    I(@"iOS Host: ViewController viewDidLoad");
    
    self.view.backgroundColor = UIColor.whiteColor;
    
    I(@"iOS Host: call main()");
    _main();
    
    I(@"iOS Host: post event AppCreate");
    CQHostOnEvent(CQHostEventAppCreate);
    
    I(@"iOS Host: post event UILoad");
    CQHostOnEvent(CQHostEventUILoad);
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"iOS Host: ViewController viewDidAppear");
    
    I(@"iOS Host: post event UIAppear");
    CQHostOnEvent(CQHostEventUIAppear);
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"iOS Host: ViewController viewDidDisappear");
    
    I(@"iOS Host: post event UIDisappear");
    CQHostOnEvent(CQHostEventUIDisappear);
}

@end
