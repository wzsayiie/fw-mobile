#import "CQBundle.h"

@interface CQBundle ()
@end

@implementation CQBundle

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT(self);
}

- (NSData *)resourceForType:(NSString *)type name:(NSString *)name {
    NSString *path = [NSBundle.mainBundle pathForResource:name ofType:type];
    if (path.length > 0) {
        return [NSData dataWithContentsOfFile:path];
    } else {
        return nil;
    }
}

@end
