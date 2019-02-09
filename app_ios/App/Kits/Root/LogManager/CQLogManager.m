#import "CQLogManager.h"
#import "CQFoundation.h"

#define FORMAT_STRING(NAME, FORMAT)\
/**/    NSString *NAME = nil; {\
/**/        va_list args;\
/**/        va_start(args, FORMAT);\
/**/        NAME = [[NSString alloc] initWithFormat:FORMAT arguments:args];\
/**/        va_end(args);\
/**/    }

@implementation CQLogManager

+ (void)infoWithFile:(const char *)file line:(int)line format:(NSString *)format, ... {
    FORMAT_STRING(message, format);
    [CQLogger info:message file:@(file) line:line];
}

+ (void)errorWithFile:(const char *)file line:(int)line format:(NSString *)format, ... {
    FORMAT_STRING(message, format);
    [CQLogger error:message file:@(file) line:line];
}

@end
