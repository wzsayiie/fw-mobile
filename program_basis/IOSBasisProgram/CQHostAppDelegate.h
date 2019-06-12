#import <UIKit/UIKit.h>

@interface CQHostAppDelegate : UIResponder <UIApplicationDelegate>

+ (instancetype)sharedObject;

@property (nonatomic) UIWindow *window;

@end
