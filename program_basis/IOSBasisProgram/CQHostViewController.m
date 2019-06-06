#import "CQHostViewController.h"
#import "cqwindow.h"

@interface CQHostViewController ()
@property (nonatomic, readonly ) GLKView *view;
@property (nonatomic, readwrite) BOOL viewVisible;
@end

@implementation CQHostViewController

- (int64_t)wid {
    return self.hash;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSNotificationCenter *n = NSNotificationCenter.defaultCenter;
    [n addObserver:self
          selector:@selector(applicationWillEnterForeground)
              name:UIApplicationWillEnterForegroundNotification
            object:nil];
    [n addObserver:self
          selector:@selector(applicationDidEnterBackground)
              name:UIApplicationDidEnterBackgroundNotification
            object:nil];
    
    //currently opengl 2.0 is supported
    self.view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:self.view.context];
    
    CGSize size = self.view.frame.size;
    _cq_notify_window_scale (self.wid, UIScreen.mainScreen.scale);
    _cq_notify_window_origin(self.wid, 0, 0);
    _cq_notify_window_size  (self.wid, size.width, size.height);
    _cq_notify_window_load  (self.wid);
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (!self.viewVisible) {
        _cq_notify_window_appear(self.wid);
        self.viewVisible = true;
    }
}

- (void)applicationWillEnterForeground {
    if (!self.viewVisible) {
        _cq_notify_window_appear(self.wid);
        self.viewVisible = true;
    }
}

- (void)applicationDidEnterBackground {
    if (self.viewVisible) {
        self.viewVisible = false;
        _cq_notify_window_disappear(self.wid);
    }
}

- (GLKView *)view {
    return (GLKView *)super.view;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    _cq_notify_window_gl_draw(self.wid);
    _cq_notify_window_update(self.wid);
}

- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    _cq_notify_window_size(self.wid, size.width, size.height);
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_began(self.wid, pt.x, pt.y);
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_moved(self.wid, pt.x, pt.y);
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_ended(self.wid, pt.x, pt.y);
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    _cq_notify_window_touch_ended(self.wid, pt.x, pt.y);
}

@end
