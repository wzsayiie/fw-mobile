//

@interface CQLogManager : NSObject

//NOTE: these static member designed for thread safe.

+ (void)printInfoWithFormat :(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);
+ (void)printErrorWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

@end

#define I(...) [CQLogManager printInfoWithFormat :__VA_ARGS__]
#define E(...) [CQLogManager printErrorWithFormat:__VA_ARGS__]
