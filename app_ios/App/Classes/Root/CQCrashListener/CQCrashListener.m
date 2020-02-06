#import "CQCrashListener.h"

@implementation CQCrashListener

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT_OF_SELF();
}

- (instancetype)init {
    if (self = [super init]) {
        I(@"crash manager initializing");
    }
    return self;
}

@end
