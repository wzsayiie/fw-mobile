#import "CQObjcBasis.h"

@interface CQBundle : NSObject

+ (instancetype)sharedObject;

- (NSData *)resourceForType:(NSString *)type name:(NSString *)name;

@end
