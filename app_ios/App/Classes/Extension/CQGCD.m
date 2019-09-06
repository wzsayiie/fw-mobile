#import "CQGCD.h"

static void async(float delayInSeconds, dispatch_queue_t queue, dispatch_block_t block) {
    if (block == NULL) {
        return;
    }
    
    if (delayInSeconds > 0) {
        dispatch_time_t time = dispatch_time(
            DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC)
        );
        dispatch_after(time, queue, block);
    } else {
        dispatch_async(queue, block);
    }
}

void cq_dispatch_async(float delayInSeconds, dispatch_block_t block) {
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    async(delayInSeconds, queue, block);
}

void cq_dispatch_on_main(float delayInSeconds, dispatch_block_t block) {
    dispatch_queue_t queue = dispatch_get_main_queue();
    async(delayInSeconds, queue, block);
}
