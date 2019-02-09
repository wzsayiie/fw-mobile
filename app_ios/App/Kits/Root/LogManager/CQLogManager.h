//

@interface CQLogManager : NSObject

//NOTE: these static member designed for thread safe.

+ (void)infoWithFile:(const char *)file line:(int)line format:(NSString *)format, ...
NS_FORMAT_FUNCTION(3, 4);

+ (void)errorWithFile:(const char *)file line:(int)line format:(NSString *)format, ...
NS_FORMAT_FUNCTION(3, 4);

@end

#define I(...) [CQLogManager  infoWithFile:__FILE__ line:__LINE__ format:__VA_ARGS__]
#define E(...) [CQLogManager errorWithFile:__FILE__ line:__LINE__ format:__VA_ARGS__]
