#import "CQCPPViewController.h"
#import "CQLog.h"
#import "cq_host_api.h"

@interface CQCPPViewController ()
@end

@implementation CQCPPViewController

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
    I(@"host event: view did load");
    
    [CQCPPViewController resetSharedObject:self reset:YES];
    _cq_notify_default_window_created(self.hash);
    _cq_notify_window_load(self.hash);
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"host event: view did appear");
    
    _cq_notify_window_show(self.hash);
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"host event: view did disappear");
    
    _cq_notify_window_hide(self.hash);
}

#pragma mark - touch event

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    I(@"host event: touches began");
    
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_began(self.hash, pt.x, pt.y);
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_moved(self.hash, pt.x, pt.y);
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    I(@"host event: touches ended");
    
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_ended(self.hash, pt.x, pt.y);
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    I(@"host event: touches cancelled");
    
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_ended(self.hash, pt.x, pt.y);
}

@end

#pragma mark - functions

static inline float range(float min, float v, float max) {
    return v < min ? min : (v > max ? max : v);
}

void _cq_window_set_back_color(int64_t window_idx, float r, float g, float b) {
    I(@"host invoke: set window background color");
    
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        
        r = range(0.f, r, 1.f);
        g = range(0.f, g, 1.f);
        b = range(0.f, b, 1.f);
        
        UIColor *color = [UIColor colorWithRed:r green:g blue:b alpha:1];
        [controller.view setBackgroundColor:color];
    }
}

float _cq_window_get_width(int64_t window_idx) {
    I(@"host invoke: get window width");
    
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        return controller.view.bounds.size.width;
    } else {
        return 0;
    }
}

float _cq_window_get_height(int64_t window_idx) {
    I(@"host invoke: get window height");
    
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        return controller.view.bounds.size.height;
    } else {
        return 0;
    }
}

float _cq_window_get_screen_scale(int64_t window_idx) {
    I(@"host invoke: get screen scale");
    
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithHash:window_idx];
    if (controller != nil) {
        return UIScreen.mainScreen.scale;
    } else {
        return 0;
    }
}
