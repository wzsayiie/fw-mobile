#import "CQCPPViewController.h"
#import "cqhostapi.h"

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

+ (instancetype)sharedObjectWithIndex:(int64_t)index {
    //there is one window on iOS, parameter 'index' is unused.
    return index ? [self resetSharedObject:nil reset:NO] : nil;
}

#pragma mark - life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [CQCPPViewController resetSharedObject:self reset:YES];
    
    I(@"host: view did load enter");
    _cq_notify_default_window_created(self.hash);
    _cq_notify_window_load(self.hash);
    I(@"host: view did load exit");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    I(@"host: view did appear enter");
    _cq_notify_window_show(self.hash);
    I(@"host: view did appear exit");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    I(@"host: view did disappear enter");
    _cq_notify_window_hide(self.hash);
    I(@"host: view did disappear exit");
}

#pragma mark - touch event

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    
    I(@"host: touches began enter");
    _cq_notify_window_touch_began(self.hash, pt.x, pt.y);
    I(@"host: touches began exit");
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    
    I(@"host: touches moved enter");
    _cq_notify_window_touch_moved(self.hash, pt.x, pt.y);
    I(@"host: touches moved exit");
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    
    I(@"host: touches ended enter");
    _cq_notify_window_touch_ended(self.hash, pt.x, pt.y);
    I(@"host: touches ended exit");
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    
    I(@"host: touches cancelled enter");
    _cq_notify_window_touch_ended(self.hash, pt.x, pt.y);
    I(@"host: touches cancelled exit");
}

@end

#pragma mark - functions

void _cq_window_set_back_color(int64_t window_idx, float r, float g, float b) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithIndex:window_idx];
    if (controller != nil) {
        UIColor *color = [UIColor colorWithRed:r green:g blue:b alpha:1];
        [controller.view setBackgroundColor:color];
    }
}

float _cq_window_get_width(int64_t window_idx) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithIndex:window_idx];
    if (controller != nil) {
        return controller.view.bounds.size.width;
    } else {
        return 0;
    }
}

float _cq_window_get_height(int64_t window_idx) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithIndex:window_idx];
    if (controller != nil) {
        return controller.view.bounds.size.height;
    } else {
        return 0;
    }
}

float _cq_window_get_screen_scale(int64_t window_idx) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithIndex:window_idx];
    if (controller != nil) {
        return UIScreen.mainScreen.scale;
    } else {
        return 0;
    }
}
