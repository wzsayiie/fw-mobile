#import "NSMutableDictionary+CQ.h"

@implementation NSMutableDictionary (CQ)

- (void)safeSetObject:(id)object forKey:(id<NSCopying>)key {
    if (object != nil && key != nil) {
        [self setObject:object forKey:key];
    }
}

@end
