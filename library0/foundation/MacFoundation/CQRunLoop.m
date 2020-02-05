#import "CQRunLoop.h"

@interface CQRunLoop ()
@property (nonatomic) NSRunLoop *core;
@end

@implementation CQRunLoop

+ (instancetype)mainRunLoop {
    static dispatch_once_t token = 0;
    static CQRunLoop *runLoop = nil;
    dispatch_once(&token, ^{
        runLoop = [[CQRunLoop alloc] init];
        runLoop.core = NSRunLoop.mainRunLoop;
    });
    return runLoop;
}

- (void)performBlock:(void (^)(void))block {
    [self.core performBlock:block];
}

@end
