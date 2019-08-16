#import "DailyDemoController.h"

@interface DailyDemoController ()
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@end

@implementation DailyDemoController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self addRow:@"alpha" action:@selector(handleActionAlpha)];
    [self addRow:@"beta"  action:@selector(handleActionBeta) ];
}

- (void)handleActionAlpha {
}

- (void)handleActionBeta {
}

@end
