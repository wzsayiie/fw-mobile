#import "ExampleViewController.h"

@interface ExampleViewController ()
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@end

@implementation ExampleViewController

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
