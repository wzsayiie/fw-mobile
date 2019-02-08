#import "CQDemoViewController.h"

@interface CQDemoViewControllerDataRow : NSObject
@property (nonatomic) NSString *text;
@property (nonatomic) NSValue *action;
@end

@implementation CQDemoViewControllerDataRow
@end

static NSString *const CQDemoViewControllerCellID = @"Cell";

@interface CQDemoViewController() <UITableViewDataSource, UITableViewDelegate>
@property (nonatomic) NSMutableArray<CQDemoViewControllerDataRow *> *dataSource;
@end

@implementation CQDemoViewController

#pragma mark - Controller Life Events

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [self loadTableViewIfNeeded];
}

- (UITableView *)tableView {
    return nil;
}

- (void)loadTableViewIfNeeded {
    
    UITableView *tableView = self.tableView;
    
    //if tableView is nil or tableView was already initialized
    if (tableView == nil || tableView.dataSource != nil) {
        return;
    }
    
    [tableView registerClass:UITableViewCell.class forCellReuseIdentifier:CQDemoViewControllerCellID];
    tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    tableView.dataSource = self;
    tableView.delegate = self;
}

- (NSMutableArray<CQDemoViewControllerDataRow *> *)dataSource {
    if (_dataSource == nil) {
        _dataSource = [NSMutableArray array];
    }
    return _dataSource;
}

- (void)addRow:(NSString *)rowText action:(SEL)action {
    if (rowText.length == 0) {
        return;
    }
    
    CQDemoViewControllerDataRow *row = [[CQDemoViewControllerDataRow alloc] init];
    row.text = rowText;
    row.action = [NSValue valueWithPointer:action];
    [self.dataSource addObject:row];
    
    [self loadTableViewIfNeeded];
    [self.tableView reloadData];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataSource.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CQDemoViewControllerCellID];
    cell.textLabel.text = self.dataSource[indexPath.row].text;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    SEL action = (SEL)self.dataSource[indexPath.row].action.pointerValue;
    if (action != nil && [self respondsToSelector:action]) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
        [self performSelector:action];
#pragma clang diagnostic pop
    }
}

@end
