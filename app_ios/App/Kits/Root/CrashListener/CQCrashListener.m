#import "CQCrashListener.h"

@implementation CQCrashListener

+ (instancetype)sharedObject {
    static id object = nil;
    if (object == nil) {
        object = [[self alloc] init];
    }
    return object;
}

- (instancetype)init {
    if (self = [super init]) {
        I(@"crash manager initializing");
    }
    return self;
}

@end
