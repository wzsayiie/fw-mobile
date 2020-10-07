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
    CQ_SHARED_OBJECT_OF_SELF();
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

- (NSArray<NSString *> *)contentsOfDirectoryAtPath:(NSString *)path error:(BOOL *)error {
    NSFileManager *manager = NSFileManager.defaultManager;
    NSError *nsError = nil;
    
    NSArray<NSString *> *contents = [manager contentsOfDirectoryAtPath:path error:&nsError];
    if (nsError == nil) {
        if (error != NULL) {
            *error = NO;
        }
        
        id comparer = ^NSComparisonResult(NSString *a, NSString *b) {
            return [a compare:b];
        };
        return [contents sortedArrayUsingComparator:comparer];
        
    } else {
        if (error != NULL) {
            *error = YES;
        }
        
        return nil;
    }
}

@end
