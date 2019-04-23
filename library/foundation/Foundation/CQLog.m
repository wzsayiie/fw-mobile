#import "CQLog.h"
#import "cqfoundationarche.h"

void CQLogInfo(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    
    if (file.length > 0 && line > 0) {
        const char *F = file.lastPathComponent.UTF8String;
        const char *M = message.UTF8String;
        fprintf(stderr, "info|%s(%04d)|%s\n", F, line, M);
    } else {
        fprintf(stderr, "info|%s\n", message.UTF8String);
    }
}

void CQLogError(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    
    if (file.length > 0 && line > 0) {
        const char *F = file.lastPathComponent.UTF8String;
        const char *M = message.UTF8String;
        fprintf(stderr, "ERROR|%s(%03d)|%s\n", F, line, M);
    } else {
        fprintf(stderr, "ERROR|%s\n", message.UTF8String);
    }
}
