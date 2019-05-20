#import "CQCPPViewController.h"
#import "cqosapi.h"

@interface CQCPPViewController ()
+ (instancetype)sharedObjectWithHash:(int64_t)hash;
@end

#pragma mark - interfaces

static float window_get_width(int64_t window_idx) {

    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        return controller.view.bounds.size.width;
    } else {
        return 0;
    }
}

static float window_get_height(int64_t window_idx) {

    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        return controller.view.bounds.size.height;
    } else {
        return 0;
    }
}

static float window_get_screen_scale(int64_t window_idx) {

    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        return UIScreen.mainScreen.scale;
    } else {
        return 0;
    }
}

@implementation CQCPPViewController

#pragma mark - object storage

+ (instancetype)resetSharedObject:(id)object reset:(BOOL)reset {
    static id shared = nil;
    if (reset) {
        shared = object;
    }
    return shared;
}

+ (instancetype)sharedObjectWithHash:(int64_t)hash {
    //there is one window on iOS, return shared object if 'hash' != 0.
    return hash ? [self resetSharedObject:nil reset:NO] : nil;
}

#pragma mark - life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    
    [CQCPPViewController resetSharedObject:self reset:YES];
    
    _cq_install_window_get_width_handler(window_get_width);
    _cq_install_window_get_height_handler(window_get_height);
    _cq_install_window_get_screen_scale_handler(window_get_screen_scale);
    
    _cq_notify_default_window_created(self.hash);
    _cq_notify_window_load(self.hash);
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];

    _cq_notify_window_show(self.hash);
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];

    _cq_notify_window_hide(self.hash);
}

#pragma mark - touch event

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_began(self.hash, pt.x, pt.y);
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_moved(self.hash, pt.x, pt.y);
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_ended(self.hash, pt.x, pt.y);
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_ended(self.hash, pt.x, pt.y);
}

@end
