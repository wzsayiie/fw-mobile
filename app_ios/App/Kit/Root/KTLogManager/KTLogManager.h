//

@interface KTLogManager : NSObject

+ (void)printInfoWithFormat :(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);
+ (void)printErrorWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

@end

#define I(...) [KTLogManager printInfoWithFormat :__VA_ARGS__]
#define E(...) [KTLogManager printErrorWithFormat:__VA_ARGS__]
