#import "CQCrashListener.h"

@implementation CQCrashListener

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT(self);
}

- (instancetype)init {
    if (self = [super init]) {
        I(@"crash manager initializing");
    }
    return self;
}

@end
