#import "CQLuaViewController.h"
#import "CQLog.h"
#import "cq_lua_source.h"
#import "cq_lua_vm.h"

@interface CQLuaViewController()
@property (nonatomic) NSString *luaDirectory;
@end

@implementation CQLuaViewController

- (NSString *)luaDirectory {
    if (_luaDirectory.length == 0) {
        
        NSSearchPathDirectory  d = NSCachesDirectory;
        NSSearchPathDomainMask m = NSUserDomainMask;
        NSString *cachesDirectory = NSSearchPathForDirectoriesInDomains(d, m, YES)[0];
        NSString *luaDirectory = [cachesDirectory stringByAppendingPathComponent:@"LUA"];
        
        NSFileManager *manager = NSFileManager.defaultManager;
        [manager createDirectoryAtPath:luaDirectory
           withIntermediateDirectories:YES attributes:nil error:nil];
        
        _luaDirectory = luaDirectory;
    }
    return _luaDirectory;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    I(@"host: view did load");
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
