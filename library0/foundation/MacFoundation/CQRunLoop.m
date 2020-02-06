#import "CQRunLoop.h"

@interface CQRunLoop ()
@property (nonatomic) NSRunLoop *core;
@end

@implementation CQRunLoop

+ (instancetype)mainRunLoop {
    CQ_SHARED_OBJECT(CQRunLoop, object, {
        object.core = NSRunLoop.mainRunLoop;
    });
}

- (void)performBlock:(void (^)(void))block {
    [self.core performBlock:block];
}

@end
