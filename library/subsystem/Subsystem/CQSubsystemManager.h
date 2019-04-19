#import <Foundation/Foundation.h>

@class CQSubsystemManager;

@protocol CQSubsystemManagerDelegate <NSObject>
- (BOOL)subsystemManager:(CQSubsystemManager *)manager startSubsystem:(NSString *)name;
- (void)subsystemManager:(CQSubsystemManager *)manager stopSubsystem:(NSString *)name;
@end

@interface CQSubsystemManager : NSObject
+ (instancetype)sharedObject;
@property (nonatomic, weak) id<CQSubsystemManagerDelegate> delegate;
@property (nonatomic, readonly) NSString *startingSubsystemName;
- (BOOL)startSubsystem:(NSString *)name;
- (void)stopSubsystem:(NSString *)name;
@end
