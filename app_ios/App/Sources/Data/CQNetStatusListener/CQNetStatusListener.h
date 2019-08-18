//

cq_declare_s(CQNotif_NetStatusDidChange);
cq_declare_s(CQNotif_NetStatusDidChange_Int_NetStatus);
cq_declare_s(CQNotif_NetStatusDidChange_Str_IPv4String);
cq_declare_s(CQNotif_NetStatusDidChange_Str_IPv6String);

typedef NS_ENUM(NSInteger, CQNetStatus) {
    CQNetStatusNone,
    CQNetStatusWWAN,
    CQNetStatusWiFi,
};

@interface CQNetStatusListener : NSObject

+ (instancetype)sharedObject;

@property (nonatomic, readonly) CQNetStatus netStatus;
@property (nonatomic, readonly) NSString *IPv4String;
@property (nonatomic, readonly) NSString *IPv6String;

@end
