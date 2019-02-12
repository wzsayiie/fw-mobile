#import "CQFoundation.h"

static id<CQLoggerAgent> sAgent = nil;

@implementation CQLogger

+ (void)info:(NSString *)message file:(NSString *)file line:(int32_t)line {
    if (sAgent != nil) {
        [sAgent loggerAgentHandleInfo:message file:file line:line];
        return;
    }
    
    const char *M = message.UTF8String;
    const char *F = file.lastPathComponent.UTF8String;
    int L = (int)line;
    fprintf(stderr, "info|%s(%d)|%s\n", F, L, M);
}

+ (void)error:(NSString *)message file:(NSString *)file line:(int32_t)line {
    if (sAgent != nil) {
        [sAgent loggerAgentHandleError:message file:file line:line];
        return;
    }
    
    const char *M = message.UTF8String;
    const char *F = file.lastPathComponent.UTF8String;
    int L = (int)line;
    fprintf(stderr, "ERROR|%s(%d)|%s\n", F, L, M);
}

+ (void)setAgent:(id<CQLoggerAgent>)agent {
    sAgent = agent;
}

@end
