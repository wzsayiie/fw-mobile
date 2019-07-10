#import "CQObjcBasis.h"

@interface CQURLSession : NSObject

+ (instancetype)sharedObject;

- (NSData *)sendSyncGet:(NSString *)urlString
                timeout:(NSTimeInterval)timeout
                  error:(NSError **)error;

@end
