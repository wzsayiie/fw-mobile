#import "UIDevice+CQ.h"
#import <sys/utsname.h>

@implementation UIDevice (CQ)

- (NSString *)hardwareType {
    struct utsname info;
    uname(&info);
    return @(info.machine);
}

@end
