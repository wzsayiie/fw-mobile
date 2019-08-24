#import "CQNetStatusListener.h"
#import <SystemConfiguration/SystemConfiguration.h>
#import <arpa/inet.h>
#import <ifaddrs.h>

cq_define_s(CQNotif_NetStatusChanged);
cq_define_s(CQNotif_NetStatusChanged_Int_PreferredStatus);
cq_define_s(CQNotif_NetStatusChanged_Bol_WWANAvailable);
cq_define_s(CQNotif_NetStatusChanged_Bol_WiFiAvailable);
cq_define_s(CQNotif_NetStatusChanged_Str_WWANIPv4);
cq_define_s(CQNotif_NetStatusChanged_Str_WiFiIPv4);
cq_define_s(CQNotif_NetStatusChanged_Str_WWANIPv6LinkLocal);
cq_define_s(CQNotif_NetStatusChanged_Str_WiFiIPv6LinkLocal);

NSString *CQStringFromNetStatus(CQNetStatus status) {
    switch (status) {
        case CQNetStatusNone: return @"CQNetStatusNone";
        case CQNetStatusWWAN: return @"CQNetStatusWWAN";
        case CQNetStatusWiFi: return @"CQNetStatusWiFi";
        default: {
            return [NSString stringWithFormat:@"Wrong CQNetStatus:%d", (int)status];
        }
    }
}

@interface CQNetStatusListener()
@property (nonatomic, assign) SCNetworkReachabilityRef reachability;
@property (nonatomic, assign) CQNetStatus preferredNetStatus;
@property (nonatomic, copy) NSString *WWANIPv4;
@property (nonatomic, copy) NSString *WiFiIPv4;
@property (nonatomic, copy) NSString *WWANIPv6LinkLocal;
@property (nonatomic, copy) NSString *WiFiIPv6LinkLocal;
@end

@implementation CQNetStatusListener

- (BOOL)WWANAvailable { return self.WWANIPv4.length > 0 || self.WWANIPv6LinkLocal.length > 0; }
- (BOOL)WiFiAvailable { return self.WiFiIPv4.length > 0 || self.WiFiIPv6LinkLocal.length > 0; }

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

- (instancetype)init {
    if (!(self = [super init])) {
        return nil;
    }
    
    //set the remote address to "0.0.0.0",
    //to listen the connectivity of the local network.
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_len = sizeof(address);
    address.sin_family = AF_INET;
    
    self.reachability = SCNetworkReachabilityCreateWithAddress(
        kCFAllocatorDefault, (struct sockaddr *)&address);
    
    //get current status.
    [self resetPreferredNetStatus:0];
    [self resetIPString];
    
    I(@"net status listener startup {");
    I(@"  preferred status: %@", CQStringFromNetStatus(self.preferredNetStatus));
    I(@"  WWAN IPv4: %@", self.WWANIPv4);
    I(@"  WiFi IPv4: %@", self.WiFiIPv4);
    I(@"  WWAN IPv6 link-local: %@", self.WWANIPv6LinkLocal);
    I(@"  WiFi IPv6 link-local: %@", self.WiFiIPv6LinkLocal);
    I(@"}");
    
    //set listener.
    SCNetworkReachabilityContext context = {0, (__bridge void *)self, NULL, NULL, NULL};
    SCNetworkReachabilitySetCallback(self.reachability, reachabilityCallBack, &context);
    
    CFRunLoopRef loop = CFRunLoopGetCurrent();
    CFRunLoopMode mode = kCFRunLoopDefaultMode;
    SCNetworkReachabilityScheduleWithRunLoop(self.reachability, loop, mode);
    
    return self;
}

- (void)dealloc {
    CFRunLoopRef loop = CFRunLoopGetCurrent();
    CFRunLoopMode mode = kCFRunLoopDefaultMode;
    SCNetworkReachabilityUnscheduleFromRunLoop(self.reachability, loop, mode);
    CFRelease(self.reachability);
}

static void reachabilityCallBack(
    SCNetworkReachabilityRef reachability, SCNetworkReachabilityFlags flags, void *object)
{
    CQNetStatusListener *listener = (__bridge CQNetStatusListener *)object;
    [listener handleNetStatusDidChangeToFlags:flags];
}

- (void)handleNetStatusDidChangeToFlags:(SCNetworkReachabilityFlags)flags {
    
    CQNetStatus preferredNetStatus = self.preferredNetStatus;
    NSString *WWANIPv4 = self.WWANIPv4;
    NSString *WiFiIPv4 = self.WiFiIPv4;
    NSString *WWANIPv6LinkLocal = self.WWANIPv6LinkLocal;
    NSString *WiFiIPv6LinkLocal = self.WiFiIPv6LinkLocal;
    
    [self resetPreferredNetStatus:flags];
    [self resetIPString];
    
    //only data changed, post the notification.
    if (preferredNetStatus == self.preferredNetStatus
     && [NSString string:WWANIPv4 isEqualToString:self.WWANIPv4]
     && [NSString string:WiFiIPv4 isEqualToString:self.WiFiIPv4]
     && [NSString string:WWANIPv6LinkLocal isEqualToString:self.WWANIPv6LinkLocal]
     && [NSString string:WiFiIPv6LinkLocal isEqualToString:self.WiFiIPv6LinkLocal])
    {
        return;
    }
    
    NSMutableDictionary *param = [NSMutableDictionary dictionary];
    [param safeSetObject:@(self.preferredNetStatus) forKey:CQNotif_NetStatusChanged_Int_PreferredStatus  ];
    [param safeSetObject:@(self.WWANAvailable)      forKey:CQNotif_NetStatusChanged_Bol_WWANAvailable    ];
    [param safeSetObject:@(self.WiFiAvailable)      forKey:CQNotif_NetStatusChanged_Bol_WiFiAvailable    ];
    [param safeSetObject:self.WWANIPv4              forKey:CQNotif_NetStatusChanged_Str_WWANIPv4         ];
    [param safeSetObject:self.WiFiIPv4              forKey:CQNotif_NetStatusChanged_Str_WiFiIPv4         ];
    [param safeSetObject:self.WWANIPv6LinkLocal     forKey:CQNotif_NetStatusChanged_Str_WWANIPv6LinkLocal];
    [param safeSetObject:self.WiFiIPv6LinkLocal     forKey:CQNotif_NetStatusChanged_Str_WiFiIPv6LinkLocal];
    
    [NOTIF post:CQNotif_NetStatusChanged param:param];
}

- (void)resetPreferredNetStatus:(SCNetworkReachabilityFlags)flags {
    
    if (flags == 0) {
        SCNetworkReachabilityGetFlags(self.reachability, &flags);
    }
    
    BOOL adapterReachable    = (flags & kSCNetworkFlagsReachable                       ) != 0;
    BOOL needExplictConnect  = (flags & kSCNetworkFlagsConnectionRequired              ) != 0;
    BOOL canConnectOnDemand  = (flags & kSCNetworkReachabilityFlagsConnectionOnDemand  ) != 0;
    BOOL canConnectOnTraffic = (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic ) != 0;
    BOOL connectMustByUser   = (flags & kSCNetworkReachabilityFlagsInterventionRequired) != 0;
    
    BOOL canConnectAutomatic = (canConnectOnDemand || canConnectOnTraffic) && !connectMustByUser;
    BOOL networkReachable = adapterReachable && (!needExplictConnect || canConnectAutomatic);
    
    if (networkReachable) {
        if ((flags & kSCNetworkReachabilityFlagsIsWWAN) != 0) {
            self.preferredNetStatus = CQNetStatusWWAN;
        } else {
            self.preferredNetStatus = CQNetStatusWiFi;
        }
    } else {
        self.preferredNetStatus = CQNetStatusNone;
    }
}

- (void)resetIPString {
    
    //NOTE: -(void)resetIPString depends self.preferredNetStatus.
    BOOL tryHoldWWANIP = (self.preferredNetStatus != CQNetStatusNone);
    BOOL tryHoldWiFiIP = (self.preferredNetStatus == CQNetStatusWiFi);
    
    self.WWANIPv4 = nil;
    self.WiFiIPv4 = nil;
    self.WWANIPv6LinkLocal = nil;
    self.WiFiIPv6LinkLocal = nil;
    
    struct ifaddrs *ifaddrs;
    if (getifaddrs(&ifaddrs) != 0) {
        return;
    }
    for (struct ifaddrs *it = ifaddrs; it; it = it->ifa_next) {
        
        BOOL holdWWANIP = tryHoldWWANIP && strcmp(it->ifa_name, "pdp_ip0") == 0;
        BOOL holdWiFiIP = tryHoldWiFiIP && strcmp(it->ifa_name, "en0") == 0;
        if (!holdWWANIP && !holdWiFiIP) {
            continue;
        }
        
        struct sockaddr_in  *a4 = (struct sockaddr_in  *)it->ifa_addr;
        struct sockaddr_in6 *a6 = (struct sockaddr_in6 *)it->ifa_addr;
        char buf[INET6_ADDRSTRLEN] = {0};
        
        if (a4->sin_family == AF_INET) {
            
            inet_ntop(AF_INET, &a4->sin_addr, buf, INET_ADDRSTRLEN);
            if (holdWWANIP) {
                self.WWANIPv4 = @(buf);
            } else {
                self.WiFiIPv4 = @(buf);
            }
            
        } else if (a6->sin6_family == AF_INET6) {
            
            inet_ntop(AF_INET6, &a6->sin6_addr, buf, INET6_ADDRSTRLEN);
            BOOL isLinkLocal = IN6_IS_ADDR_LINKLOCAL(&a6->sin6_addr);
            if (!isLinkLocal) {
                continue;
            }
            
            if (holdWWANIP) {
                self.WWANIPv6LinkLocal = @(buf);
            } else {
                self.WiFiIPv6LinkLocal = @(buf);
            }
        }
    }
    freeifaddrs(ifaddrs);
}

@end
