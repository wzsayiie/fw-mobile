#import "CQLog.h"
#import "cqfoundationarche.h"

static void Info(NSString *file, int line, NSString *msg) {
    if (file.length > 0 && line > 0) {
        const char *F = file.lastPathComponent.UTF8String;
        const char *M = msg.UTF8String;
        fprintf(stderr, "info|%s(%04d)|%s\n", F, line, M);
    } else {
        fprintf(stderr, "info|%s\n", msg.UTF8String);
    }
}

static void Error(NSString *file, int line, NSString *msg) {
    if (file.length > 0 && line > 0) {
        const char *F = file.lastPathComponent.UTF8String;
        const char *M = msg.UTF8String;
        fprintf(stderr, "ERROR|%s(%03d)|%s\n", F, line, M);
    } else {
        fprintf(stderr, "ERROR|%s\n", msg.UTF8String);
    }
}

void cq_log_info (const char *file, int32_t line, const char *msg) {Info (@(file), line, @(msg));}
void cq_log_error(const char *file, int32_t line, const char *msg) {Error(@(file), line, @(msg));}

void CQLogInfo(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    Info(file, line, [[NSString alloc] initWithFormat:format arguments:args]);
    va_end(args);
}
void CQLogError(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    Error(file, line, [[NSString alloc] initWithFormat:format arguments:args]);
    va_end(args);
}
