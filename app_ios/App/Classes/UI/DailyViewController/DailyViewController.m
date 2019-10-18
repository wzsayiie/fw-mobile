#import "DailyViewController.h"
#import "BlankViewController.h"
#import "CommandViewController.h"

@interface DailyViewController ()
@end

@implementation DailyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setTabItemController:CommandViewController.class forTitle:@"Command"];
    [self setTabItemController:BlankViewController.class forTitle:@"Blank"];
}

- (void)setTabItemController:(Class)clazz forTitle:(NSString *)title {
    UIViewController *controller = [[clazz alloc] init];
    controller.tabBarItem.title = title;
    [self addChildViewController:controller];
}

@end
