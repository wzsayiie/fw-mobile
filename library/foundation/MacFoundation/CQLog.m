#import "CQLog.h"
#import "cqfoundationarche.h"

static void logging(NSString *tag, NSString *file, int line, NSString *message) {
    if (file.length > 0 && line > 0) {
        NSLog(@"%@|%@(%04d)|%@\n", tag, file, line, message);
    } else {
        NSLog(@"%@|%@\n", tag, message);
    }
}

void CQLogInfo(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    logging(@"I", file.lastPathComponent, line, message);
}

void CQLogError(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    logging(@"E", file.lastPathComponent, line, message);
}
