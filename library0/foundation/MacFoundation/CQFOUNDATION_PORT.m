#import "CQFoundation.h"
#import "cqfoundationarche.h"

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
    CQLogInfo(@(file), line, @"%s", message);
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    CQLogError(@(file), line, @"%s", message);
}

//app bundle resource:

const char *cq_ios_bundle_path(void) {
    NSString *path = CQBundle.mainBundle.bundlePath;
    return cq_store_str(path.UTF8String);
}

const char *cq_ios_resource_path(const char *name, const char *type) {
    NSString *path = [CQBundle.mainBundle resourcePathForName:@(name) type:@(type)];
    return cq_store_str(path.UTF8String);
}

void cq_ios_resource(const char *name, const char *type, cq_bytes_out out) {
    NSData *data = [CQBundle.mainBundle resourceForName:@(type) type:@(type)];
    cq_oc_bytes_assign(data, out);
}

void cq_android_asset(const char *name, cq_bytes_out out) {
}

bool cq_android_copy_asset(const char *from_path, const char *to_path) {
    return false;
}

//file access:

const char *cq_document_directory(void) {
    NSString *directory = CQDocumentDirectory();
    return cq_store_str(directory.UTF8String);
}

const char *cq_caches_directory(void) {
    NSString *directory = CQCachesDirectory();
    return cq_store_str(directory.UTF8String);
}

const char *cq_temporary_directory(void) {
    NSString *directory = CQTemporaryDirectory();
    return cq_store_str(directory.UTF8String);
}

bool cq_directory_exists(const char *path) {
    return [CQFileManager.sharedObject directoryExistsAtPath:@(path)];
}

bool cq_file_exists(const char *path) {
    return [CQFileManager.sharedObject fileExistsAtPath:@(path)];
}

bool cq_create_directory(const char *path, bool intermediate) {
    CQFileManager *n = CQFileManager.sharedObject;
    return [n createDirectoryAtPath:@(path) intermediate:intermediate];
}

void cq_remove_path(const char *path) {
    [CQFileManager.sharedObject removeItemAtPath:@(path)];
}

void cq_sub_files(const char *path, cq_str_list_out out) {
    CQFileManager *manager = CQFileManager.sharedObject;
    NSArray<NSString *> *contents = [manager contentsOfDirectoryAtPath:@(path) error:NULL];
    cq_oc_str_list_assign(contents, out);
}

//thread:

void cq_thread_run(cq_block block, void *data) {
    if (block != NULL) {
        CQThreadRun(^{ cq_run_block(block, data); });
    }
}

void cq_thread_sleep(float seconds) {
    CQThreadSleep(seconds);
}

//main run loop:

void cq_main_loop_post(cq_block block, void * data) {
    if (block != NULL) {
        [CQRunLoop.mainRunLoop performBlock:^{ cq_run_block(block, data); }];
    }
}

//http(s):

@interface CQHTTPSessionPortObject : CQHTTPSession <CQHTTPSessionDelegate>

@property (nonatomic) cq_http_body_reader   send_body_reader;
@property (nonatomic) cq_http_code_writer   recv_code_writer;
@property (nonatomic) cq_http_header_writer recv_header_writer;
@property (nonatomic) cq_http_body_writer   recv_body_writer;

@property (nonatomic) void *userData;
@property (nonatomic) BOOL waitResponse;

@end

@implementation CQHTTPSessionPortObject

- (void)syncResumeWithUserData:(void *)userData {
    
    self.userData = userData;
    self.waitResponse = YES;
    self.delegate = self;
    
    [self syncResume];
}

- (NSInteger)HTTPSession:(CQHTTPSession *)session
   requestBodyFromBuffer:(void *)buffer
            bufferLength:(NSInteger)bufferLength
{
    if (self.send_body_reader != NULL) {
        return self.send_body_reader(self.userData, buffer, (int32_t)bufferLength);
    } else {
        return -1;
    }
}

- (void)handleResponseHeaderFromSession:(CQHTTPSession *)session {
    if (self.recv_code_writer != NULL) {
        self.recv_code_writer(self.userData, (int32_t)session.responseCode);
    }
    if (self.recv_header_writer != NULL) {
        for (NSString *field in session.responseHeader) {
            NSString *value = session.responseHeader[field];
            self.recv_header_writer(self.userData, field.UTF8String, value.UTF8String);
        }
    }
}

- (BOOL)HTTPSession:(CQHTTPSession *)session responseBodyData:(NSData *)data {
    if (self.waitResponse) {
        [self handleResponseHeaderFromSession:session];
        self.waitResponse = NO;
    }
    
    if (self.recv_body_writer != NULL) {
        return self.recv_body_writer(self.userData, data.bytes, (int32_t)data.length);
    } else {
        return YES;
    }
}

@end

typedef NSMutableDictionary<NSNumber *, CQHTTPSessionPortObject *> CQHTTPSessionPortDict;

static CQHTTPSessionPortDict *CQHTTPSessionPortStore(void) {
    static CQHTTPSessionPortDict *dict = nil;
    if (dict == nil) {
        dict = [NSMutableDictionary dictionary];
    }
    return dict;
}

static CQHTTPSessionPortObject *CQHTTPSessionPortGet(cq_http *http) {
    if (http != NULL) {
        CQHTTPSessionPortDict *dict = CQHTTPSessionPortStore();
        NSNumber *hash = @((NSUInteger)http);
        return dict[hash];
    } else {
        return nil;
    }
}

cq_http *cq_http_create(void) {
    CQHTTPSessionPortObject *port = [[CQHTTPSessionPortObject alloc] init];
    cq_http *hash = (cq_http *)port.hash;
    
    CQHTTPSessionPortDict *dict = CQHTTPSessionPortStore();
    dict[@(port.hash)] = port;
    
    return hash;
}

void cq_http_destroy(cq_http *http) {
    CQHTTPSessionPortDict *dict = CQHTTPSessionPortStore();
    NSNumber *hash = @((NSUInteger)http);
    [dict removeObjectForKey:hash];
}

void cq_http_timeout(cq_http *http, float seconds) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    port.timeoutSeconds = seconds;
}

void cq_http_send_method(cq_http *http, const char *method) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    if (!cq_str_empty(method)) {
        port.method = @(method);
    } else {
        port.method = nil;
    }
}

void cq_http_send_url(cq_http *http, const char *url) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    if (!cq_str_empty(url)) {
        port.URLString = @(url);
    } else {
        port.URLString = nil;
    }
}

void cq_http_send_query(cq_http *http, const char *field, const char *value) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    if (!cq_str_empty(field) && !cq_str_empty(value)) {
        [port setURLQueryField:@(field) value:@(value)];
    }
}

void cq_http_send_header(cq_http *http, const char *field, const char *value) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    if (!cq_str_empty(field) && !cq_str_empty(value)) {
        [port setRequestHeaderField:@(field) value:@(value)];
    }
}

void cq_http_send_body_from(cq_http *http, cq_http_body_reader reader) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    port.send_body_reader = reader;
}

void cq_http_recv_code_to(cq_http *http, cq_http_code_writer writer) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    port.recv_code_writer = writer;
}

void cq_http_recv_header_to(cq_http *http, cq_http_header_writer writer) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    port.recv_header_writer = writer;
}

void cq_http_recv_body_to(cq_http *http, cq_http_body_writer writer) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    port.recv_body_writer = writer;
}

void cq_http_sync(cq_http *http, void *user) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    [port syncResumeWithUserData:user];
}

const char *cq_http_error(cq_http *http) {
    CQHTTPSessionPortObject *port = CQHTTPSessionPortGet(http);
    
    return cq_store_str(port.error.description.UTF8String);
}
