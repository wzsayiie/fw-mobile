#import "NSBundle+KT.h"

@implementation NSBundle (KT)

- (NSString *)appVersion {
    NSDictionary *info = NSBundle.mainBundle.infoDictionary;
    NSString *shortVersion = info[@"CFBundleShortVersionString"];
    NSString *buildVersion = info[@"CFBundleVersion"];
    return [NSString stringWithFormat:@"%@-%@", shortVersion, buildVersion];
}

@end
