#import "KTLogManager.h"
#import "CQFoundation.h"

#define FORMAT_STRING(NAME, FORMAT)\
/**/    NSString *NAME = nil; {\
/**/        va_list args;\
/**/        va_start(args, FORMAT);\
/**/        NAME = [[NSString alloc] initWithFormat:FORMAT arguments:args];\
/**/        va_end(args);\
/**/    }

@implementation KTLogManager

+ (void)printInfoWithFormat:(NSString *)format, ... {
    FORMAT_STRING(message, format);
    [CQLogger info:message];
}

+ (void)printErrorWithFormat:(NSString *)format, ... {
    FORMAT_STRING(message, format);
    [CQLogger error:message];
}

@end
