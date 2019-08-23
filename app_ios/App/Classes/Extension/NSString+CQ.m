#import "NSString+CQ.h"

@implementation NSString (CQ)

+ (BOOL)string:(NSString *)a isEqualToString:(NSString *)b {
    if (a == nil && b == nil) {
        return YES;
    }
    return [a isEqualToString:b];
}

@end
