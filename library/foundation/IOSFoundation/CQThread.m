#import "CQThread.h"

@interface CQThread : NSThread
@property (nonatomic) void (^task)(void);
@end

@implementation CQThread

- (void)main {
    if (self.task != nil) {
        self.task();
    }
}

@end

void CQThreadRun(void (^task)(void)) {
    if (task != nil) {
        CQThread *thread = [[CQThread alloc] init];
        thread.task = task;
        [thread start];
    }
}

void CQThreadSleep(float seconds) {
    if (seconds > 0) {
        [NSThread sleepForTimeInterval:seconds];
    }
}
