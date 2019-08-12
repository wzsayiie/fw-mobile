#import "CQGCD.h"

void _dispatch_async(dispatch_block_t block) {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), block);
}

void _dispatch_async_on_main(dispatch_block_t block) {
    dispatch_async(dispatch_get_main_queue(), block);
}
