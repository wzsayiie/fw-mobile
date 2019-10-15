#import "DailyViewController.h"
#import "ActionViewController.h"
#import "BlankViewController.h"

@interface DailyViewController ()
@end

@implementation DailyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setTabItemController:ActionViewController.class forTitle:@"Action"];
    [self setTabItemController:BlankViewController.class  forTitle:@"Blank" ];
}

- (void)setTabItemController:(Class)clazz forTitle:(NSString *)title {
    UIViewController *controller = [[clazz alloc] init];
    controller.tabBarItem.title = title;
    [self addChildViewController:controller];
}

@end
