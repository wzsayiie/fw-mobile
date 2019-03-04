#import "CQFoundation.h"
#import "CQLogger.h"

static id<CQLoggerAgent> sAgent = nil;

@implementation CQLogger

+ (void)info:(NSString *)message file:(NSString *)file line:(int32_t)line {
    if (sAgent != nil) {
        [sAgent loggerAgentHandleInfo:message file:file line:line];
        return;
    }
    
    if (file.length > 0 && line > 0) {
        const char *M = message.UTF8String;
        const char *F = file.lastPathComponent.UTF8String;
        int L = (int)line;
        fprintf(stderr, "info|%s(%d)|%s\n", F, L, M);
    } else {
        fprintf(stderr, "info|%s\n", message.UTF8String);
    }
}

+ (void)error:(NSString *)message file:(NSString *)file line:(int32_t)line {
    if (sAgent != nil) {
        [sAgent loggerAgentHandleError:message file:file line:line];
        return;
    }
    
    if (file.length > 0 && line > 0) {
        const char *M = message.UTF8String;
        const char *F = file.lastPathComponent.UTF8String;
        int L = (int)line;
        fprintf(stderr, "ERROR|%s(%d)|%s\n", F, L, M);
    } else {
        fprintf(stderr, "ERROR|%s\n", message.UTF8String);
    }
}

+ (void)setAgent:(id<CQLoggerAgent>)agent {
    sAgent = agent;
}

@end

void _I(const char *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    [CQLogger info:message file:@(file) line:line];
    
    va_end(args);
}

void _E(const char *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    [CQLogger error:message file:@(file) line:line];
    
    va_end(args);
}
