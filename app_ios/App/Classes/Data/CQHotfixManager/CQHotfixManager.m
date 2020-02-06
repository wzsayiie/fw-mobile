#import "CQHotfixManager.h"

@implementation CQHotfixManager

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT_OF_SELF();
}

- (instancetype)init {
    if (self = [super init]) {
        I(@"hotfix manager initializing");
    }
    return self;
}

@end
