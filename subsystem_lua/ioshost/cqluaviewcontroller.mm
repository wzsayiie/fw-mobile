#import "cqluaviewcontroller.h"
#import "cqluasource.hh"
#import "cqluavm.hh"

static std::string CQLuaPath() {
    
    NSString *cachePath = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES)[0];
    NSString *luaPath = [cachePath stringByAppendingPathComponent:@"LUA"];
    
    NSFileManager *fileManager = NSFileManager.defaultManager;
    [fileManager createDirectoryAtPath:luaPath withIntermediateDirectories:YES attributes:nil error:nil];
    
    return luaPath.UTF8String;
}

@interface CQLuaViewController()
@end

@implementation CQLuaViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    I(@"iOS Host: ViewController viewDidLoad");
    
    self.view.backgroundColor = UIColor.whiteColor;
    
    std::string luaPath = CQLuaPath();
    CQLuaSourceUpdate(luaPath);
    CQLuaVMOpen(luaPath);
    
    I(@"iOS Host: call main()");
    CQLuaVMDoString("main()");
    
    I(@"iOS Host: post event AppCreate");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.AppCreate)");
    
    I(@"iOS Host: post event UILoad");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UILoad)");
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    I(@"iOS Host: ViewController viewDidAppear");
    
    I(@"iOS Host: post event UIAppear");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIAppear)");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    I(@"iOS Host: ViewController viewDidDisappear");
    
    I(@"iOS Host: post event UIDisappear");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIDisappear)");
}

@end
