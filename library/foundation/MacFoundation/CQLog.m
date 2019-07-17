#import "CQLog.h"
#import "cqfoundationarche.h"

static void logging(NSString *tag, NSString *file, int line, NSString *format, va_list args) {
    if (format.length == 0) {
        return;
    }
    
    //[NSString initWithFormat:arguments:] depends on local text encoding,
    //use vsnprintf() to splice utf-8 string.
    char buffer[1024 * 4];
    vsnprintf(buffer, sizeof(buffer), format.UTF8String, args);
    NSString *message = [NSString stringWithUTF8String:buffer];
    
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
