#import "NSObject+CQSingleton.h"
#import "CQSingletonManager.h"

@implementation NSObject (CQSingleton)

+ (instancetype)sharedObject {
    return [CQSingletonManager.sharedObject objectForClass:self];
}

@end
