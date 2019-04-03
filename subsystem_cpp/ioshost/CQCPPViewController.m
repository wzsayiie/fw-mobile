#import "CQCPPViewController.h"
#import "cqhostapi.h"

@interface CQCPPViewController ()

@property (nonatomic) BOOL hostViewVisible;

@property (nonatomic) cq_window *userWindow;
@property (nonatomic) BOOL userWindowLoaded;
@property (nonatomic) float userBackColorR;
@property (nonatomic) float userBackColorG;
@property (nonatomic) float userBackColorB;

@end

@implementation CQCPPViewController

+ (instancetype)resetSharedObject:(id)object reset:(BOOL)reset {
    static id shared = nil;
    if (reset) {
        shared = object;
    }
    return shared;
}

+ (instancetype)sharedObjectWithPtr:(cq_window *)ptr {
    //there is one window on iOS, parameter 'ptr' is unused.
    return ptr ? [self resetSharedObject:nil reset:NO] : nil;
}

+ (instancetype)sharedObject {
    return [self resetSharedObject:nil reset:NO];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    I(@"iOS Host: viewDidLoad enter");
    {
        [CQCPPViewController resetSharedObject:self reset:YES];
        _entry();
    }
    I(@"iOS Host: viewDidLoad exit");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"iOS Host: viewDidAppear enter");
    {
        self.hostViewVisible = YES;
        if (self.userWindow->procedure.show && self.userWindowLoaded) {
            self.userWindow->procedure.show(self.userWindow);
        }
    }
    I(@"iOS Host: viewDidAppear exit");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"iOS Host: viewDidDisappear enter");
    {
        self.hostViewVisible = NO;
        if (self.userWindow->procedure.hide && self.userWindowLoaded) {
            self.userWindow->procedure.hide(self.userWindow);
        }
    }
    I(@"iOS Host: viewDidDisappear exit");
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    if (self.userWindowLoaded) {
        if (self.userWindow->procedure.touch_began) {
            self.userWindow->procedure.touch_began(self.userWindow, pt.x, pt.y);
        }
    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    if (self.userWindowLoaded) {
        if (self.userWindow->procedure.touch_moved) {
            self.userWindow->procedure.touch_moved(self.userWindow, pt.x, pt.y);
        }
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    if (self.userWindowLoaded) {
        if (self.userWindow->procedure.touch_ended) {
            self.userWindow->procedure.touch_ended(self.userWindow, pt.x, pt.y);
        }
    }
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGPoint pt = [touches.anyObject locationInView:self.view];
    if (self.userWindowLoaded) {
        if (self.userWindow->procedure.touch_ended) {
            self.userWindow->procedure.touch_ended(self.userWindow, pt.x, pt.y);
        }
    }
}

@end

cq_window *cq_window_create(void) {
    //on iOS, only one window can be created
    CQCPPViewController *controller = [CQCPPViewController sharedObject];
    if (controller.userWindow == NULL) {
        controller.userWindow = calloc(sizeof(cq_window), 1);
        return controller.userWindow;
    } else {
        return NULL;
    }
}

void cq_window_load(cq_window *window) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithPtr:window];
    if (controller == nil) {
        return;
    }
    if (controller.userWindowLoaded) {
        return;
    }
    
    //life cycle ->
    controller.userWindowLoaded = YES;
    if (controller.userWindow->procedure.load) {
        controller.userWindow->procedure.load(controller.userWindow);
    }
    if (controller.userWindow->procedure.show && controller.hostViewVisible) {
        controller.userWindow->procedure.show(controller.userWindow);
    }
    
    //properties ->
    float r = controller.userBackColorR;
    float g = controller.userBackColorG;
    float b = controller.userBackColorB;
    UIColor *color = [UIColor colorWithRed:r green:g blue:b alpha:1];
    [controller.view setBackgroundColor:color];
}

void cq_window_set_back_color(cq_window *window, float r, float g, float b) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithPtr:window];
    if (controller == nil) {
        return;
    }
    
    controller.userBackColorR = r;
    controller.userBackColorG = g;
    controller.userBackColorB = b;
    if (controller.userWindowLoaded) {
        UIColor *color = [UIColor colorWithRed:r green:g blue:b alpha:1];
        [controller.view setBackgroundColor:color];
    }
}

float cq_window_get_width(cq_window *window) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithPtr:window];
    if (controller.userWindowLoaded) {
        return controller.view.bounds.size.width;
    } else {
        return 0;
    }
}

float cq_window_get_height(cq_window *window) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithPtr:window];
    if (controller.userWindowLoaded) {
        return controller.view.bounds.size.height;
    } else {
        return 0;
    }
}

float cq_window_get_screen_scale(cq_window *window) {
    CQCPPViewController *controller = [CQCPPViewController sharedObjectWithPtr:window];
    if (controller.userWindowLoaded) {
        return UIScreen.mainScreen.scale;
    } else {
        return 0;
    }
}
