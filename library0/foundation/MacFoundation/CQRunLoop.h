#import "CQObjcBasis.h"

@interface CQRunLoop : NSObject

+ (instancetype)mainRunLoop;

- (void)performBlock:(void (^)(void))block;

@end
