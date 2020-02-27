#import "CQGLViewController.h"
#import "cqwnd.h"

@interface CQGLViewController ()
@property (nonatomic, readonly ) GLKView *view;
@property (nonatomic, readwrite) BOOL viewVisible;
@property (nonatomic, readwrite) int64_t wndID;
@property (nonatomic, readwrite) BOOL wndLoaded;
@end

@implementation CQGLViewController

static CQGLViewController *sGLViewController = nil;

static float   wnd_scale(void     ) {return [sGLViewController windowScale ];}
static int64_t new_wnd  (void     ) {return [sGLViewController createWindow];}
static void    show_wnd (int64_t i) {return [sGLViewController showWindow:i];}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //currently opengl 3.0 is supported.
    self.view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    [EAGLContext setCurrentContext:self.view.context];
    
    //install notifications.
    NSNotificationCenter *n = NSNotificationCenter.defaultCenter;
    [n addObserver:self
          selector:@selector(applicationWillEnterForeground)
              name:UIApplicationWillEnterForegroundNotification
            object:nil];
    [n addObserver:self
          selector:@selector(applicationDidEnterBackground)
              name:UIApplicationDidEnterBackgroundNotification
            object:nil];
    
    //install functions.
    sGLViewController = self;
    _cq_wndport port = {NULL}; {
        port.wnd_scale = wnd_scale;
        port.new_wnd   = new_wnd;
        port.show_wnd  = show_wnd;
    }
    _cq_init_wndport(&port);
    
    //entry.
    if (self.coreAppEntry != NULL) {
        self.coreAppEntry();
    }
}

- (float)windowScale {
    return UIScreen.mainScreen.scale;
}

- (int64_t)createWindow {
    
    //only one window can be created on ios.
    if (self.wndID != 0) {
        return 0;
    }
    
    self.wndID = 1;
    return self.wndID;
}

- (void)showWindow:(int64_t)wndID {
    if (wndID != self.wndID) {
        return;
    }
    
    CGSize size = self.view.frame.size;
    _cq_wnd_origin(self.wndID, 0, 0);
    _cq_wnd_size(self.wndID, size.width, size.height);
    
    if (!self.wndLoaded) {
        self.wndLoaded = YES;
        _cq_wnd_load(self.wndID);
    }
    if (self.viewVisible) {
        _cq_wnd_appear(self.wndID);
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (!self.viewVisible) {
        self.viewVisible = YES;
        
        if (self.wndLoaded) {
            _cq_wnd_appear(self.wndID);
        }
    }
}

- (void)applicationWillEnterForeground {
    if (!self.viewVisible) {
        self.viewVisible = YES;
        
        if (self.wndLoaded) {
            _cq_wnd_appear(self.wndID);
        }
    }
}

- (void)applicationDidEnterBackground {
    if (self.viewVisible) {
        self.viewVisible = NO;
        
        if (self.wndLoaded) {
            _cq_wnd_disappear(self.wndID);
        }
    }
}

- (GLKView *)view {
    return (GLKView *)super.view;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    if (self.wndLoaded) {
        //NOTE: put update() before gldraw(). update data above all.
        _cq_wnd_update(self.wndID);
        _cq_wnd_gldraw(self.wndID);
    }
}

- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    if (self.wndLoaded) {
        _cq_wnd_size(self.wndID, size.width, size.height);
    }
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    if (self.wndLoaded) {
        CGPoint pt = [touches.anyObject locationInView:self.view];
        _cq_wnd_pbegan(self.wndID, pt.x, pt.y);
    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    if (self.wndLoaded) {
        CGPoint pt = [touches.anyObject locationInView:self.view];
        _cq_wnd_pmoved(self.wndID, pt.x, pt.y);
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    if (self.wndLoaded) {
        CGPoint pt = [touches.anyObject locationInView:self.view];
        _cq_wnd_pended(self.wndID, pt.x, pt.y);
    }
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    if (self.wndLoaded) {
        CGPoint pt = [touches.anyObject locationInView:self.view];
        _cq_wnd_pended(self.wndID, pt.x, pt.y);
    }
}

@end
