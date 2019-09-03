//

//post $block to dispatch_get_global_queue().
void _dispatch_async(float delayInSeconds, dispatch_block_t block);

void _dispatch_async_on_main(float delayInSeconds, dispatch_block_t block);
