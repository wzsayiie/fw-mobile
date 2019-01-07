#import "NSObject+KTSingleton.h"
#import "KTSingletonManager.h"

@implementation NSObject (KTSingleton)

+ (instancetype)sharedObject {
    return [KTSingletonManager.sharedObject objectForClass:self];
}

@end
