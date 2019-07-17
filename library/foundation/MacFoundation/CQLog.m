#import "CQLog.h"
#import "cqfoundationarche.h"

static void logging(NSString *tag, NSString *file, int line, NSString *message) {
    if (file.length > 0 && line > 0) {
        NSLog(@"%@|%@(%04d)|%@", tag, file, line, message);
    } else {
        NSLog(@"%@|%@", tag, message);
    }
}

void CQLogInfo(NSString *file, int line, NSString *format, ...) {
    //[NSString initWithFormat:arguments:] depends on local text encoding,
    //use vsnprintf() to splice utf-8 string.
    char buffer[1024]; {
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format.UTF8String, args);
        va_end(args);
    }
    NSString *message = [NSString stringWithUTF8String:buffer];
    logging(@"I", file.lastPathComponent, line, message);
}

void CQLogError(NSString *file, int line, NSString *format, ...) {
    char buffer[1024]; {
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format.UTF8String, args);
        va_end(args);
    }
    NSString *message = [NSString stringWithUTF8String:buffer];
    logging(@"E", file.lastPathComponent, line, message);
}
