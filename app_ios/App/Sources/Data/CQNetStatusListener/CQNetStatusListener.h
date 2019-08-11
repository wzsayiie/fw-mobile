//

extern NSNotificationName const CQNetStatusDidChangeNotification;

typedef NS_ENUM(NSInteger, CQNetStatus) {
    CQNetStatusNone,
    CQNetStatusWWAN,
    CQNetStatusWiFi,
};

@interface CQNetStatusListener : NSObject

+ (instancetype)sharedObject;

@property (nonatomic, readonly) CQNetStatus status;

@end
