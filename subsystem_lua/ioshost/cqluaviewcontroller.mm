#import "cqluaviewcontroller.h"
#import "cqluasource.hh"
#import "cqluavm.hh"

@interface CQLuaViewController()
@end

@implementation CQLuaViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    
    NSString *cachePath = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject;
    NSString *luaPath = [cachePath stringByAppendingPathComponent:@"LUA"];
    
    NSFileManager *fileManager = NSFileManager.defaultManager;
    [fileManager createDirectoryAtPath:luaPath withIntermediateDirectories:YES attributes:nil error:nil];
    
    CQLuaSourceUpdate(luaPath.UTF8String, [=]() {
        
        CQLuaVMOpen(luaPath.UTF8String);
        
        CQLuaVMDoString("main()");
        CQLuaVMDoString("CQHost:onEvent(CQHost.Event.AppCreate)");
        CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UILoad)");
    });
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIAppear)");
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIDisappear)");
}

@end
