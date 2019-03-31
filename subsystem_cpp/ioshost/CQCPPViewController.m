#import "CQCPPViewController.h"
#import "cqhostapi.h"

@interface CQCPPViewController ()
@end

@implementation CQCPPViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    I(@"iOS Host: ViewController viewDidLoad");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"iOS Host: ViewController viewDidAppear");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"iOS Host: ViewController viewDidDisappear");
}

@end

cq_window *cq_window_create(void) {
    return NULL;
}

void cq_window_show(cq_window *window) {
}

void cq_window_set_background_color(cq_window *window, float r, float g, float b) {
}

void cq_window_set_procedure(cq_window *window, cq_window_procedure *procedure) {
}

cq_window_procedure *cq_window_get_procedure(cq_window *window) {
    return NULL;
}
