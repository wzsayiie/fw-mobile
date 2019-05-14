#import "CQLuaViewController.h"
#import "CQFoundation.h"

#import "cqluasource.h"
#import "cqluavm.h"
#import "cqlualibfoundation.h"
#import "cqlualibsubsystem.h"
#import "cqlualibuikit.h"

@interface CQLuaViewController()
@property (nonatomic) NSString *luaDirectory;
@end

@implementation CQLuaViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    I(@"host event: view did load");
    
    cq_lua_open_vm();
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    cq_lua_load_lib_uikit();
    
    cq_lua_run_scripts();
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"host event: view did appear");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"host event: view did disappear");
}

@end
