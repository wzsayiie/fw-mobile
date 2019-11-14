#import "CQObjcBasis.h"

//WARNING: don't use CQHTTPSession on main thread, which will result in a deadlock.
//
//CQHTTPSession internally uses the NSURLSession, NSURLSession relies on the main RunLoop event.
//in order to implement synchronous network access, CQHTTPSession uses a signal lock,
//that will suspend the current RunLoop.

@class CQHTTPSession;

@protocol CQHTTPSessionDelegate <NSObject>

@optional

//return length of read bytes, if no more bytes could be read, return -1;
- (NSInteger)HTTPSession:(CQHTTPSession *)session
   requestBodyFromBuffer:(void *)buffer
            bufferLength:(NSInteger)bufferLength;

//return NO means stop transfer.
- (BOOL)HTTPSession:(CQHTTPSession *)session responseBodyData:(NSData *)data;

@end

@interface CQHTTPSession : NSObject

@property (nonatomic, weak) id<CQHTTPSessionDelegate> delegate;

@property (nonatomic) NSTimeInterval timeoutSeconds;
@property (nonatomic, copy) NSString *method;
@property (nonatomic, copy) NSString *URLString;

//CQHTTPSession will perform the percent escape on its own.
- (void)setURLQueryField:(NSString *)field value:(NSString *)value;
- (void)setRequestHeaderField:(NSString *)field value:(NSString *)value;

//if the delegate implement -(NSInteger)HTTPSession:requestBodyFromBuffer:bufferLength:,
//the session will use it to get request body, else the request body from here.
@property (nonatomic) NSData *requestBodyData;

- (void)syncResume;

@property (nonatomic, readonly) NSError *error;
@property (nonatomic, readonly) NSInteger responseCode;
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *responseHeader;

//if the delegate implement -(BOOL)HTTPSession:responseBodyData:,
//the session will use it to write response body, else the response body stores into here.
@property (nonatomic, readonly) NSData *responseBodyData;

@end
