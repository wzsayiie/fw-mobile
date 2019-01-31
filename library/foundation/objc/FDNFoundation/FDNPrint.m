#import "FDNFoundation.h"

static id<FDNLoggerAgent> sAgent = nil;

@implementation FDNLogger

+ (void)info:(NSString *)message {
    if (sAgent != nil) {
        [sAgent loggerAgentHandleInfoMessage:message];
        return;
    }
    
    #if defined(DEBUG)
        fprintf(stderr, "info|%s\n", message.UTF8String);
    #else
        NSLog(@"info|%@", message);
    #endif
}

+ (void)error:(NSString *)message {
    if (sAgent != nil) {
        [sAgent loggerAgentHandleErrorMessage:message];
        return;
    }
    
    #if defined(DEBUG)
        fprintf(stderr, "ERROR|%s\n", message.UTF8String);
    #else
        NSLog(@"ERROR|%@", message);
    #endif
}

+ (void)setAgent:(id<FDNLoggerAgent>)agent {
    sAgent = agent;
}

@end
