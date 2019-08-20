#import "CQHotfixManager.h"

@implementation CQHotfixManager

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

- (instancetype)init {
    if (self = [super init]) {
        I(@"hotfix manager initializing");
    }
    return self;
}

@end
