#import "CQLogManager.h"
#import "CQFoundation.h"

@implementation CQLogManager

+ (void)infoWithFile:(const char *)file line:(int)line format:(NSString *)format, ... {
    va_list args;
    va_start(args, format);
    
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    [CQLogger info:message file:@(file) line:line];
    
    va_end(args);
}

+ (void)errorWithFile:(const char *)file line:(int)line format:(NSString *)format, ... {
    va_list args;
    va_start(args, format);
    
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args];
    [CQLogger error:message file:@(file) line:line];
    
    va_end(args);
}

@end
