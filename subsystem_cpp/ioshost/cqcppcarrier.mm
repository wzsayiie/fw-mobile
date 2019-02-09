#import <UIKit/UIKit.h>
#import "cqhost_p.hh"

//entry

extern "C" void _main();

//root view controller

@interface CQCPPCarrierController : UIViewController
@end

@implementation CQCPPCarrierController

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

//application delegate

@interface CQCPPCarrierAppDelegate : UIResponder <UIApplicationDelegate>
@property (nonatomic) UIWindow *window;
@end

@implementation CQCPPCarrierAppDelegate

- (BOOL) /* ------ */ application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    self.window.rootViewController = [[CQCPPCarrierController alloc] init];
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
