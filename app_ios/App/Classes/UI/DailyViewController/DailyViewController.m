#import "DailyViewController.h"
#import "ActionViewController.h"
#import "BlankViewController.h"

@interface DailyViewController ()
@end

@implementation DailyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    ActionViewController *action = [[ActionViewController alloc] init];
    action.tabBarItem.title = @"Action";
    [self addChildViewController:action];
    
    BlankViewController *blank = [[BlankViewController alloc] init];
    blank.tabBarItem.title = @"Blank";
    [self addChildViewController:blank];
}

@end
