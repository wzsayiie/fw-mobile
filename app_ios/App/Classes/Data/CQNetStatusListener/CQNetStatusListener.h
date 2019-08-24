//

cq_declare_s(CQNotif_NetStatusChanged);
cq_declare_s(CQNotif_NetStatusChanged_Int_PreferredStatus);
cq_declare_s(CQNotif_NetStatusChanged_Bol_WWANAvailable);
cq_declare_s(CQNotif_NetStatusChanged_Bol_WiFiAvailable);
cq_declare_s(CQNotif_NetStatusChanged_Str_WWANIPv4);
cq_declare_s(CQNotif_NetStatusChanged_Str_WiFiIPv4);
cq_declare_s(CQNotif_NetStatusChanged_Str_WWANIPv6LinkLocal);
cq_declare_s(CQNotif_NetStatusChanged_Str_WiFiIPv6LinkLocal);

typedef NS_ENUM(NSInteger, CQNetStatus) {
    CQNetStatusNone,
    CQNetStatusWWAN,
    CQNetStatusWiFi,
};
NSString *CQStringFromNetStatus(CQNetStatus status);

@interface CQNetStatusListener : NSObject

+ (instancetype)sharedObject;

//CQNetStatusWiFi has preferred.
@property (nonatomic, readonly) CQNetStatus preferredNetStatus;

//NOTE: WWAN and WiFi may be both available.
@property (nonatomic, readonly) BOOL WWANAvailable;
@property (nonatomic, readonly) BOOL WiFiAvailable;

@property (nonatomic, readonly) NSString *WWANIPv4;
@property (nonatomic, readonly) NSString *WiFiIPv4;

@property (nonatomic, readonly) NSString *WWANIPv6LinkLocal;
@property (nonatomic, readonly) NSString *WiFiIPv6LinkLocal;

@end
