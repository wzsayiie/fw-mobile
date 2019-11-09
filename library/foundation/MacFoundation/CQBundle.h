#import "CQObjcBasis.h"

@interface CQBundle : NSObject

+ (instancetype)mainBundle;

@property (nonatomic, readonly) NSString *bundlePath;

- (NSData *)resourceForType:(NSString *)type name:(NSString *)name;

@end
