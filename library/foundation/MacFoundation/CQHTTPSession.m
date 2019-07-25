#import "CQHTTPSession.h"

@interface CQHTTPSessionBodyInputStream : NSInputStream
@property (nonatomic, weak) CQHTTPSession *session;
@property (nonatomic) NSStreamStatus status;
@end

@implementation CQHTTPSessionBodyInputStream

//NOTE: NSStream requires these methods to be implemented.
- (void)setDelegate:(id<NSStreamDelegate>)delegate {}
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode {}

- (NSStreamStatus)streamStatus {
    return self.status;
}

- (void)open {
    self.status = NSStreamStatusOpen;
}

- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)bufferLength {
    if (self.session.requestBodyReader != NULL) {
        NSInteger readLength = self.session.requestBodyReader(self.session, buffer, bufferLength);
        if (readLength >= 0) {
            self.status = NSStreamStatusReading;
            return readLength;
        } else {
            //if no more data can be read, requestBodyReader returns -1.
            self.status = NSStreamStatusAtEnd;
            return 0;
        }
    } else {
        self.status = NSStreamStatusAtEnd;
        return 0;
    }
}

- (BOOL)hasBytesAvailable {
    switch (self.status) {
        case NSStreamStatusOpen   : return YES;
        case NSStreamStatusReading: return YES;
        default: return NO;
    }
}

- (void)close {
    self.status = NSStreamStatusClosed;
}

@end

@interface CQHTTPSession () <NSURLSessionDelegate>

@property (nonatomic) NSMutableDictionary<NSString *, NSString *> *requestHeader;
@property (nonatomic) NSMutableDictionary<NSString *, NSString *> *URLQuery;
@property (nonatomic) CQHTTPSessionBodyInputStream *requestBodyStream;

@property (nonatomic) dispatch_semaphore_t semaphore;

@property (nonatomic) NSError *error;
@property (nonatomic) NSInteger responseCode;
@property (nonatomic) NSDictionary<NSString *, NSString *> *responseHeader;
@property (nonatomic) NSData *responseBodyData;

@end

@implementation CQHTTPSession

- (void)setURLQueryField:(NSString *)filed value:(NSString *)value {
    if (filed.length == 0 || value.length == 0) {
        return;
    }
    
    if (self.URLQuery == nil) {
        self.URLQuery = [NSMutableDictionary dictionary];
    }
    self.URLQuery[filed] = value;
}

- (void)setRequestHeaderField:(NSString *)field value:(NSString *)value {
    if (field.length == 0 || value.length) {
        return;
    }
    
    if (self.requestHeader == nil) {
        self.requestHeader = [NSMutableDictionary dictionary];
    }
    self.requestHeader[field] = value;
}

- (void)syncResume {
    
    //reset:
    self.error = nil;
    self.responseCode = 0;
    self.responseHeader = nil;
    self.responseBodyData = nil;
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    
    //request timeout:
    if (self.timeoutSeconds > 0) {
        request.timeoutInterval = self.timeoutSeconds;
    }
    
    //request method:
    if (self.method.length == 0) {
        self.method = @"GET";
    }
    request.HTTPMethod = self.method.uppercaseString;
    
    //request url:
    NSMutableString *queryString = [NSMutableString string]; {
        for (NSString *field in self.URLQuery) {
            [queryString appendString:(queryString.length == 0 ? @"?" : @"&")];
            [queryString appendString:field];
            [queryString appendString:@"="];
            [queryString appendString:self.URLQuery[field]];
        }
    }
    NSMutableString *URLString = [NSMutableString string];
    [URLString appendString:self.URLString];
    [URLString appendString:queryString];
    request.URL = [NSURL URLWithString:URLString];
    
    //request header:
    [request setAllHTTPHeaderFields:self.requestHeader];
    
    //request body:
    if (self.requestBodyReader != NULL) {
        self.requestBodyStream = [[CQHTTPSessionBodyInputStream alloc] init];
        self.requestBodyStream.session = self;
    } else {
        request.HTTPBody = self.requestBodyData;
    }
    
    //task
    NSURLSessionConfiguration *config = NSURLSessionConfiguration.defaultSessionConfiguration;
    NSURLSession *session = [NSURLSession sessionWithConfiguration:config
        delegate:self delegateQueue:NSOperationQueue.mainQueue];
    
    self.semaphore = dispatch_semaphore_create(0);
    NSURLSessionTask *task = nil; {
        if ([request.HTTPMethod isEqualToString:@"POST"]
         || [request.HTTPMethod isEqualToString:@"PUT"])
        {
            task = [session uploadTaskWithStreamedRequest:request];
        }
        else
        {
            task = [session dataTaskWithRequest:request];
        }
    }
    [task resume];
    dispatch_semaphore_wait(self.semaphore, DISPATCH_TIME_FOREVER);
}

- (void)URLSession:(NSURLSession *)session
              task:(NSURLSessionTask *)task
 needNewBodyStream:(void (^)(NSInputStream *))completionHandler
{
    completionHandler(self.requestBodyStream);
}

- (void)URLSession:(NSURLSession *)session
          dataTask:(NSURLSessionDataTask *)dataTask
    didReceiveData:(NSData *)data
{
    //when body responsed, header should be available.
    if (self.responseCode == 0) {
        NSHTTPURLResponse *response = (NSHTTPURLResponse *)dataTask.response;
        self.responseCode = response.statusCode;
        self.responseHeader = response.allHeaderFields;
    }
    
    if (self.responseBodyWriter != NULL) {
        
        BOOL finishAndContinue = self.responseBodyWriter(self, data.bytes, data.length);
        if (!finishAndContinue) {
            [session invalidateAndCancel];
        }
        
    } else {
        
        if (self.responseBodyData == nil) {
            self.responseBodyData = [NSMutableData data];
        }
        NSMutableData *body = (NSMutableData *)self.responseBodyData;
        [body appendBytes:data.bytes length:data.length];
    }
}

- (void) /**/ URLSession:(NSURLSession *)session
                    task:(NSURLSessionTask *)task
    didCompleteWithError:(NSError *)error
{
    self.error = error;
    [session finishTasksAndInvalidate];
    
    dispatch_semaphore_signal(self.semaphore);
}

@end
