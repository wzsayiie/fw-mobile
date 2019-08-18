#import "CQNetStatusListener.h"

cq_define_s(CQNotif_NetStatusDidChange);
cq_define_s(CQNotif_NetStatusDidChange_Int_NetStatus);
cq_define_s(CQNotif_NetStatusDidChange_Str_IPv4String);
cq_define_s(CQNotif_NetStatusDidChange_Str_IPv6String);

@interface CQNetStatusListener()
@property (nonatomic, assign) CQNetStatus netStatus;
@property (nonatomic, copy) NSString *IPv4String;
@property (nonatomic, copy) NSString *IPv6String;
@end

@implementation CQNetStatusListener

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

@end
