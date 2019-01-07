#import "UIDeviceKT.h"
#import <sys/utsname.h>

@implementation UIDevice (KT)

- (NSString *)hardwareType {
    struct utsname info;
    uname(&info);
    return @(info.machine);
}

@end
