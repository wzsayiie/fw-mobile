#import "FDNFoundation.h"

@implementation FDNLogger

+ (void)info:(NSString *)message {
    [self printWithTag:@"info" message:message];
}

+ (void)error:(NSString *)message {
    [self printWithTag:@"ERROR" message:message];
}

+ (void)printWithTag:(NSString *)tag message:(NSString *)message {
    if (message.length > 0) {
        //NSLog(@"%@|%@", tag, message);
        fprintf(stderr, "%s|%s\n", tag.UTF8String, message.UTF8String);
    }
}

@end
