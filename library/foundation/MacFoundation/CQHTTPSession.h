#import "CQObjcBasis.h"

//WARNING: don't use CQHTTPSession on main thread, which will result in a deadlock.
//
//CQHTTPSEssion internally uses the NSURLSession implemention,
//NSURLSession relies on the main RunLoop event.
//in order to implement synchronous network access, CQHTTPSession uses a signal lock,
//that will suspend the current RunLoop.

@class CQHTTPSession;

//return length of read bytes, if no more bytes could be read, return -1;
typedef NSInteger (^CQHTTPRequestBodyReader)(CQHTTPSession *session, void *buffer, NSInteger length);

//return NO means stop transfer.
typedef BOOL (^CQHTTPResponseBodyWriter)(CQHTTPSession *session, const void *bytes, NSInteger length);

@interface CQHTTPSession : NSObject

@property (nonatomic) NSString *method;
@property (nonatomic) NSString *URLString;

- (void)setURLQueryField:(NSString *)filed value:(NSString *)value;
- (void)setRequestHeaderField:(NSString *)field value:(NSString *)value;

//if set $requestBodyReader, the session will use it to get request body,
//else the request body from $requestBodyData.
@property (nonatomic) CQHTTPRequestBodyReader requestBodyReader;
@property (nonatomic) NSData *requestBodyData;

- (void)syncResume;

@property (nonatomic, readonly) NSInteger responseCode;
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *responseHeader;

//if set $responseBodyWriter, the session will use it to write response body,
//else the response body stores into $responseBodyData.
@property (nonatomic) CQHTTPResponseBodyWriter responseBodyWriter;
@property (nonatomic, readonly) NSData *responseBodyData;

@property (nonatomic) NSTimeInterval timeoutSeconds;

@end
