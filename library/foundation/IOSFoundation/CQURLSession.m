#import "CQURLSession.h"

@implementation CQURLSession

+ (instancetype)sharedObject {
    cq_shared_object(self);
}

- (NSData *)sendSyncGet:(NSString *)urlString
                timeout:(NSTimeInterval)timeout
                  error:(NSError **)error
{
    //1 request data
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    request.HTTPMethod = @"GET";
    request.timeoutInterval = timeout;
    
    //2 connect
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    __block NSData *retData = nil;
    __block NSError *retError = nil;
    
    NSURLSession* session = NSURLSession.sharedSession;
    NSURLSessionDataTask *task =
    [session dataTaskWithRequest:request
           completionHandler:^(NSData *data, NSURLResponse *response, NSError *error)
    {
        retData = data;
        retError = error;
        dispatch_semaphore_signal(semaphore);
    }];
    [task resume];
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    
    //3 return
    if (error != NULL) {
        *error = retError;
    }
    return retData;
}

@end
