#import "CQCrashListener.h"

@implementation CQCrashListener

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

- (instancetype)init {
    if (self = [super init]) {
        I(@"crash manager initializing");
    }
    return self;
}

@end
