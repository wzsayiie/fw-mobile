#import "CQObjcBasis.h"

@interface CQBundle : NSObject

+ (instancetype)mainBundle;

@property (nonatomic, readonly) NSString *bundlePath;

- (NSString *)resourcePathForName:(NSString *)name type:(NSString *)type;
- (NSData *)resourceForName:(NSString *)name type:(NSString *)type;

@end
