#import "CQBundle.h"

@interface CQBundle ()
@property (nonatomic) NSBundle *core;
@end

@implementation CQBundle

+ (instancetype)mainBundle {
    static dispatch_once_t token = 0;
    static CQBundle *bundle = nil;
    dispatch_once(&token, ^{
        bundle = [[CQBundle alloc] init];
        bundle.core = NSBundle.mainBundle;
    });
    return bundle;
}

- (NSString *)bundlePath {
    return self.core.bundlePath;
}

- (NSString *)resourcePathForType:(NSString *)type name:(NSString *)name {
    return [self.core pathForResource:name ofType:type];
}

- (NSData *)resourceForType:(NSString *)type name:(NSString *)name {
    NSString *path = [self.core pathForResource:name ofType:type];
    if (path.length > 0) {
        return [NSData dataWithContentsOfFile:path];
    } else {
        return nil;
    }
}

@end
