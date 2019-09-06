//

//post $block to dispatch_get_global_queue().
void cq_dispatch_async(float delayInSeconds, dispatch_block_t block);

void cq_dispatch_on_main(float delayInSeconds, dispatch_block_t block);
