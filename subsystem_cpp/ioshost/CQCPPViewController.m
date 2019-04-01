#import "CQCPPViewController.h"
#import "cqhostapi.h"

static CQCPPViewController *sHostController = nil;
static cq_window *s_user_window = NULL;

struct cq_window {
    cq_window_procedure procedure;
    
    //life cycle ->
    bool loaded;
    
    //properties ->
    float back_color_r;
    float back_color_g;
    float back_color_b;
    
    void *extra;
};

@interface CQCPPViewController ()
@property (nonatomic) BOOL viewVisible;
@end

@implementation CQCPPViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    I(@"iOS Host: viewDidLoad enter");
    {
        sHostController = self;
        _entry();
    }
    I(@"iOS Host: viewDidLoad exit");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"iOS Host: viewDidAppear enter");
    {
        self.viewVisible = YES;
        if (s_user_window != NULL && s_user_window->loaded) {
            if (s_user_window->procedure.show != NULL) {
                s_user_window->procedure.show(s_user_window);
            }
        }
    }
    I(@"iOS Host: viewDidAppear exit");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"iOS Host: viewDidDisappear enter");
    {
        self.viewVisible = NO;
        if (s_user_window != NULL && s_user_window->loaded) {
            if (s_user_window->procedure.hide != NULL) {
                s_user_window->procedure.hide(s_user_window);
            }
        }
    }
    I(@"iOS Host: viewDidDisappear exit");
}

@end

cq_window *cq_window_create(void) {
    
    //on iOS, only one window can be created
    if (s_user_window == NULL) {
        s_user_window = malloc(sizeof(cq_window));
        memset(s_user_window, 0, sizeof(cq_window));
        return s_user_window;
    } else {
        return NULL;
    }
}

void cq_window_load(cq_window *window) {
    if (window == NULL) {
        return;
    }
    if (window->loaded) {
        return;
    }
    
    //life cycle ->
    window->loaded = true;
    if (window->procedure.load != NULL) {
        window->procedure.load(window);
    }
    if (window->procedure.show != NULL && sHostController.viewVisible) {
        window->procedure.show(window);
    }
    
    //properties ->
    float back_r = window->back_color_r;
    float back_g = window->back_color_g;
    float back_b = window->back_color_b;
    UIColor *back_color = [UIColor colorWithRed:back_r green:back_g blue:back_b alpha:1];
    [sHostController.view setBackgroundColor:back_color];
}

void cq_window_set_back_color(cq_window *window, float r, float g, float b) {
    if (window == NULL) {
        return;
    }
    
    window->back_color_r = r;
    window->back_color_g = g;
    window->back_color_b = b;
    if (window->loaded) {
        UIColor *color = [UIColor colorWithRed:r green:g blue:b alpha:1];
        [sHostController.view setBackgroundColor:color];
    }
}

float cq_window_get_width(cq_window *window) {
    if (window != NULL) {
        return sHostController.view.bounds.size.width;
    } else {
        return 0;
    }
}

float cq_window_get_height(cq_window *window) {
    if (window != NULL) {
        return sHostController.view.bounds.size.height;
    } else {
        return 0;
    }
}

float cq_window_get_screen_scale(cq_window *window) {
    if (window != NULL) {
        return UIScreen.mainScreen.scale;
    } else {
        return 0;
    }
}

void cq_window_set_procedure(cq_window *window, cq_window_procedure *procedure) {
    if (window == NULL) {
        return;
    }
    
    if (procedure == NULL) {
        memset(&window->procedure, 0, sizeof(cq_window_procedure));
    } else {
        window->procedure = *procedure;
    }
}

cq_window_procedure *cq_window_get_procedure(cq_window *window) {
    if (window != NULL) {
        return &window->procedure;
    } else {
        return NULL;
    }
}

void cq_window_set_extra(cq_window *window, void *extra) {
    if (window != NULL) {
        window->extra = extra;
    }
}

void *cq_window_get_extra(cq_window *window) {
    if (window != NULL) {
        return window->extra;
    } else {
        return NULL;
    }
}
