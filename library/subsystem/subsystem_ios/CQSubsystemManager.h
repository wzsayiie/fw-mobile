#import "CQObjcBasis.h"

@interface CQSubsystemManager : NSObject

+ (instancetype)sharedObject;

- (void)startSubsystem;
- (void)stopSubsystem;

@end
