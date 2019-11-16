#import "CQObjcBasis.h"

@interface CQBundle : NSObject

+ (instancetype)mainBundle;

@property (nonatomic, readonly) NSString *bundlePath;

- (NSString *)resourcePathForType:(NSString *)type name:(NSString *)name;
- (NSData *)resourceForType:(NSString *)type name:(NSString *)name;

@end
