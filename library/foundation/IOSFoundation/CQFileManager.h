#import "CQBasis.h"

NSString *CQDocumentDirectory(void);
NSString *CQCachesDirectory(void);
NSString *CQTemporaryDirectory(void);
NSString *CQAppendPath(NSString *parent, NSString *child);

@interface CQFileManager : NSObject

+ (instancetype)sharedObject;

- (BOOL)directoryExistsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)createDirectoryAtPath:(NSString *)path intermediate:(BOOL)intermediate;
- (void)removeItemAtPath:(NSString *)path;

@end
