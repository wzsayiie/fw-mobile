#import <UIKit/UIKit.h>
#import "chost_p.h"

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
    CHostOnEvent(CHostEventAppCreate);
    CHostOnEvent(CHostEventUILoad);
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    CHostOnEvent(CHostEventUIAppear);
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    CHostOnEvent(CHostEventUIDisappear);
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
