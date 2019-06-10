#import <Foundation/Foundation.h>

@interface CQSubsystemManager : NSObject

+ (instancetype)sharedObject;

- (void)startSubsystem;
- (void)stopSubsystem;

@end
