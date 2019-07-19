#import "CQFileManager.h"

NSString *CQDocumentDirectory(void) {
    return NSSearchPathForDirectoriesInDomains
    (NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
}

NSString *CQCachesDirectory(void) {
    return NSSearchPathForDirectoriesInDomains
    (NSCachesDirectory, NSUserDomainMask, YES).firstObject;
}

NSString *CQTemporaryDirectory(void) {
    return NSTemporaryDirectory();
}

@implementation CQFileManager

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

- (BOOL)directoryExistsAtPath:(NSString *)path {
    NSFileManager *manager = NSFileManager.defaultManager;
    BOOL isDirectory = NO;
    BOOL exists = [manager fileExistsAtPath:path isDirectory:&isDirectory];
    return exists && isDirectory;
}

- (BOOL)fileExistsAtPath:(NSString *)path {
    NSFileManager *manager = NSFileManager.defaultManager;
    BOOL isDirectory = NO;
    BOOL exists = [manager fileExistsAtPath:path isDirectory:&isDirectory];
    return exists && !isDirectory;
}

- (BOOL)createDirectoryAtPath:(NSString *)path intermediate:(BOOL)intermediate {
    NSFileManager *manager = NSFileManager.defaultManager;
    return [manager createDirectoryAtPath:path
              withIntermediateDirectories:intermediate
                               attributes:nil
                                    error:nil];
}

- (void)removeItemAtPath:(NSString *)path {
    NSFileManager *manager = NSFileManager.defaultManager;
    [manager removeItemAtPath:path error:nil];
}

@end
