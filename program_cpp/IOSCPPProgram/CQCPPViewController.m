#import "CQCPPViewController.h"
#import "cqosapi.h"

@interface CQCPPViewController ()
@property (nonatomic) BOOL viewVisible;
@end

@implementation CQCPPViewController

- (int64_t)wid {
    return self.hash;
}

#pragma mark - life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    CGSize size = self.view.frame.size;
    
    _cq_notify_window_scale (self.wid, UIScreen.mainScreen.scale);
    _cq_notify_window_origin(self.wid, 0, 0);
    _cq_notify_window_size  (self.wid, size.width, size.height);
    _cq_notify_window_load  (self.wid);
    
    NSNotificationCenter *n = NSNotificationCenter.defaultCenter;
    [n addObserver:self
          selector:@selector(applicationWillEnterForeground)
              name:UIApplicationWillEnterForegroundNotification
            object:nil];
    [n addObserver:self
          selector:@selector(applicationDidEnterBackground)
              name:UIApplicationDidEnterBackgroundNotification
            object:nil];
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

#pragma mark - rotation

- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    _cq_notify_window_size(self.wid, size.width, size.height);
}

#pragma mark - touch event

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
