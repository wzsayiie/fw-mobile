#import "CQLog.h"
#import "cqfoundationintf.h"

static void logging(NSString *tag, NSString *file, int line, NSString *format, va_list args) {
    if (format.length == 0) {
        return;
    }
    
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    if (file.length > 0 && line > 0) {
        NSLog(@"%@|%@(%04d)|%@", tag, file.lastPathComponent, line, message);
    } else {
        NSLog(@"%@|%@", tag, message);
    }
}

void CQLogInfo(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    logging(@"I", file, line, format, args);
    va_end(args);
}

void CQLogError(NSString *file, int line, NSString *format, ...) {
    va_list args;
    va_start(args, format);
    logging(@"E", file, line, format, args);
    va_end(args);
}
