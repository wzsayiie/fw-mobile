#import "CQNetStatusListener.h"

@interface CQNetStatusListener()
@property (nonatomic, assign) CQNetStatus status;
@end

@implementation CQNetStatusListener

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

@end
