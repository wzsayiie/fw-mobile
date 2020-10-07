#import "CQBundle.h"

@interface CQBundle ()
@property (nonatomic) NSBundle *core;
@end

@implementation CQBundle

+ (instancetype)mainBundle {
    CQ_SHARED_OBJECT(CQBundle, object, {
        object.core = NSBundle.mainBundle;
    });
}

- (NSString *)bundlePath {
    return self.core.bundlePath;
}

- (NSString *)resourcePathForName:(NSString *)name type:(NSString *)type {
    return [self.core pathForResource:name ofType:type];
}

- (NSData *)resourceForName:(NSString *)name type:(NSString *)type {
    NSString *path = [self.core pathForResource:name ofType:type];
    if (path.length > 0) {
        return [NSData dataWithContentsOfFile:path];
    } else {
        return nil;
    }
}

@end
