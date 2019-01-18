#import "FDNFoundation.h"

@interface FDNLogger ()
@property (nonatomic) NSString *tag;
@end

@implementation FDNLogger

+ (instancetype)info {
    static FDNLogger *object = nil;
    if (object == nil) {
        object = [[FDNLogger alloc] init];
        object.tag = @"info";
    }
    return object;
}

+ (instancetype)error {
    static FDNLogger *object = nil;
    if (object == nil) {
        object = [[FDNLogger alloc] init];
        object.tag = @"ERROR";
    }
    return object;
}

- (void)print:(NSString *)text {
    if (text.length > 0) {
        //NSLog(@"%@|%@", self.tag, text);
        fprintf(stderr, "%s|%s\n", self.tag.UTF8String, text.UTF8String);
    }
}

@end
