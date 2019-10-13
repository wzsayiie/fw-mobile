#import "DocViewController.h"
#import "AttachViewController.h"
#import "ContentViewController.h"
#import "TitleBarViewController.h"
#import "ToolBarViewController.h"

@interface DocViewController ()

@property (nonnull, strong) IBOutlet UIView *vesselView;
@property (nonnull, strong) IBOutlet UIView *contentView;
@property (nonnull, strong) IBOutlet UIView *attachView;
@property (nonnull, strong) IBOutlet UIView *titleBarView;
@property (nonnull, strong) IBOutlet UIView *toolBarView;

@property (nonnull, strong) ContentViewController  *contentViewController;
@property (nonnull, strong) AttachViewController   *attachViewController;
@property (nonnull, strong) TitleBarViewController *titleBarViewController;
@property (nonnull, strong) ToolBarViewController  *toolBarViewController;

@property (nonatomic, strong) NSTimer *barsHideTimer;
@property (nonatomic, assign) BOOL barsShown;

@end

@implementation DocViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //1. data status initialize:
    self.barsShown = YES;
    
    //2. ui status initailize:
    [self adjustContainViewToSize:self.view.bounds.size];
    
    self.vesselView  .isVoid = YES;
    self.contentView .isVoid = YES;
    self.attachView  .isVoid = YES;
    self.titleBarView.isVoid = YES;
    self.toolBarView .isVoid = YES;
    
    self.contentViewController  = [[ContentViewController  alloc] init];
    self.attachViewController   = [[AttachViewController   alloc] init];
    self.titleBarViewController = [[TitleBarViewController alloc] init];
    self.toolBarViewController  = [[ToolBarViewController  alloc] init];
    
    [self safeView:self.contentView  addChildController:self.contentViewController ];
    [self safeView:self.attachView   addChildController:self.attachViewController  ];
    [self safeView:self.titleBarView addChildController:self.titleBarViewController];
    [self safeView:self.toolBarView  addChildController:self.toolBarViewController ];
    
    //bring title bar and tool bar to the front,
    //to avoid being covered by contentViewController.view.
    [self.contentView bringSubviewToFront:self.titleBarView];
    [self.contentView bringSubviewToFront:self.toolBarView ];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] init];
    [tap addTarget:self action:@selector(handleContentViewTap:)];
    [self.contentView addGestureRecognizer:tap];
    
    [self restartBarsHideTimer:YES];
}

- (void)handleContentViewTap:(UITapGestureRecognizer *)tap {
    if (self.barsShown) {
        [self showBars:NO];
        [self restartBarsHideTimer:NO];
    } else {
        [self showBars:YES];
        [self restartBarsHideTimer:YES];
    }
}

- (void)handleBarsHideTimer:(NSTimer *)timer {
    [self showBars:NO];
    [self restartBarsHideTimer:NO];
}

- (void)restartBarsHideTimer:(BOOL)enabled {
    
    if (self.barsHideTimer != nil) {
        [self.barsHideTimer invalidate];
        self.barsHideTimer = nil;
    }
    
    if (enabled) {
        CQ_WEAK(weakSelf, self);
        self.barsHideTimer =
        [NSTimer scheduledTimerWithTimeInterval:5 repeats:NO block:^(NSTimer *timer) {
            [weakSelf handleBarsHideTimer:timer];
        }];
    }
}

- (void)showBars:(BOOL)shown {
    if (self.barsShown && !shown) {
        
        self.barsShown = shown;
        [UIView animateWithDuration:1 animations:^{
            self.titleBarView.alpha = 0;
            self.toolBarView.alpha = 0;
        }];
        
    } else if (!self.barsShown && shown) {
        
        self.barsShown = shown;
        [UIView animateWithDuration:1 animations:^{
            self.titleBarView.alpha = 1;
            self.toolBarView.alpha = 1;
        }];
    }
}

- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [self adjustContainViewToSize:size];
}

- (void)adjustContainViewToSize:(CGSize)size {
    
    cq_strain_remove(self.view, self.vesselView);
    
    id safeArea = self.view.safeAreaLayoutGuide;
    
    //for landscape orientation, containView will extend to the home indicator.
    id LEFT  = safeArea;
    id RIGHT = safeArea;
    id TOP   = safeArea;
    id BOTT  = (size.width < size.height ? safeArea : self.view);
    
    cq_strain_begin();
    cq_strain_set(self.vesselView, S_LEFT , S_EQUAL, LEFT , S_LEFT , 1, 0);
    cq_strain_set(self.vesselView, S_RIGHT, S_EQUAL, RIGHT, S_RIGHT, 1, 0);
    cq_strain_set(self.vesselView, S_TOP  , S_EQUAL, TOP  , S_TOP  , 1, 0);
    cq_strain_set(self.vesselView, S_BOTT , S_EQUAL, BOTT , S_BOTT , 1, 0);
    cq_strain_end(self.view);
}

@end
