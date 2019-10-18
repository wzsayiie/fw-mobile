#import "CommandViewController.h"

@interface CommandViewController ()
@property (nonatomic, weak) IBOutlet UITableView *tableView;
@end

@implementation CommandViewController

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
