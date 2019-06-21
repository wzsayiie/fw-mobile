#import "NSBundle+CQ.h"

@implementation NSBundle (CQ)

- (NSString *)appVersion {
    NSDictionary *info = NSBundle.mainBundle.infoDictionary;
    NSString *shortVersion = info[@"CFBundleShortVersionString"];
    NSString *buildVersion = info[@"CFBundleVersion"];
    return [NSString stringWithFormat:@"%@-%@", shortVersion, buildVersion];
}

@end

NSString *L(NSString *name) {
    return NSLocalizedStringFromTable(name, @"L", nil);
}
