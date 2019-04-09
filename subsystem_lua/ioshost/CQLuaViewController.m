#import "CQLuaViewController.h"
#import "CQLog.h"

@interface CQLuaViewController()
@property (nonatomic) NSString *luaDirectory;
@end

@implementation CQLuaViewController

- (NSString *)luaDirectory {
    if (_luaDirectory.length == 0) {
        NSString *cachesDirectory = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES)[0];
        NSString *luaDirectory = [cachesDirectory stringByAppendingPathComponent:@"LUA"];
        
        NSFileManager *manager = NSFileManager.defaultManager;
        [manager createDirectoryAtPath:luaDirectory withIntermediateDirectories:YES attributes:nil error:nil];
        
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
