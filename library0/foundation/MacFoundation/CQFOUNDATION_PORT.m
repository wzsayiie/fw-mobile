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
    cq_oc_set_bytes(data, out);
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
    cq_oc_set_str_list(contents, out);
}

//thread:

void cq_thread_run(cq_block *block) {
    if (block == NULL) {
        return;
    }
    
    cq_block_retain(block);
    CQThreadRun(^{
        cq_block_run(block);
        cq_block_release(block);
    });
}

void cq_thread_sleep(float seconds) {
    CQThreadSleep(seconds);
}

//main run loop:

void cq_main_loop_post(cq_block *block) {
    if (block == NULL) {
        return;
    }
    
    cq_block_retain(block);
    [CQRunLoop.mainRunLoop performBlock:^{
        cq_block_run(block);
        cq_block_release(block);
    }];
}

//http(s):

@interface CQHTTPSessionEntity : CQHTTPSession <CQHTTPSessionDelegate>
@property (nonatomic) cq_http *handle;

@property (nonatomic) BOOL    sendBodyFinish;
@property (nonatomic) void   *sendBodyBuffer;
@property (nonatomic) int32_t sendBodyBufferLength;
@property (nonatomic) int32_t sendBodyLength;

@property (nonatomic) NSData *receiveBodyData;
@property (nonatomic) BOOL    receiveBodyStop;
@end

@implementation CQHTTPSessionEntity

- (instancetype)init {
    if (self = [super init]) {
        self.delegate = self;
    }
    return self;
}

- (void)syncResume {
    self.sendBodyFinish = NO;
    [super syncResume];
}

- (NSInteger)HTTPSession:(CQHTTPSession *)session
   requestBodyFromBuffer:(void *)buffer
            bufferLength:(NSInteger)bufferLength
{
    //NOTE: if transfer finished, return -1.
    if (self.sendBodyFinish) {
        return -1;
    }
    
    self.sendBodyBuffer = buffer;
    self.sendBodyBufferLength = (int32_t)bufferLength;
    self.sendBodyLength = 0;
    cq_http_emit(self.handle, CQ_HTTP_SEND_BODY);
    
    if (self.sendBodyLength > 0) {
        return self.sendBodyLength;
    }
    
    if (self.sendBodyFinish) {
        return -1;
    } else {
        //no data this time.
        return 0;
    }
}

- (BOOL)HTTPSession:(CQHTTPSession *)session responseBodyData:(NSData *)data {
    self.receiveBodyData = data;
    self.receiveBodyStop = NO;
    cq_http_emit(self.handle, CQ_HTTP_RECV_BODY);
    
    //REMEMBER: assign the reference to nil.
    self.receiveBodyData = nil;
    
    BOOL continuous = !self.receiveBodyStop;
    return continuous;
}

@end

cq_http *cq_http_create(void) {
    CQHTTPSessionEntity *entity = [[CQHTTPSessionEntity alloc] init];
    cq_http *handle = (cq_http *)cq_object_retain_oc(entity, @"HTTPSession");
    
    entity.handle = handle;
    
    return handle;
}

#define http_session_cast(ENTITY, HANDLE)\
/**/    CQHTTPSessionEntity *ENTITY = cq_object_oc((cq_object *)HANDLE, CQHTTPSessionEntity.class);\

void cq_http_timeout(cq_http *http, float seconds) {
    http_session_cast(object, http) {
        object.timeoutSeconds = seconds;
    }
}

void cq_http_send_method(cq_http *http, const char *method) {
    http_session_cast(object, http) {
        object.method = CQNullableString(method);
    }
}

void cq_http_send_url(cq_http *http, const char *url) {
    http_session_cast(object, http) {
        object.URLString = CQNullableString(url);
    }
}

void cq_http_send_query(cq_http *http, const char *field, const char *value) {
    http_session_cast(object, http) {
        if (cq_str_empty(field)) {return;}
        if (cq_str_empty(value)) {return;}
        
        [object setURLQueryField:@(field) value:@(value)];
    }
}

void cq_http_send_header(cq_http *http, const char *field, const char *value) {
    http_session_cast(object, http) {
        if (cq_str_empty(field)) {return;}
        if (cq_str_empty(value)) {return;}
        
        [object setRequestHeaderField:@(field) value:@(value)];
    }
}

void cq_http_sync(cq_http *http) {
    http_session_cast(object, http) {
        [object syncResume];
    }
}

int32_t cq_http_send_body_cap(cq_http *http) {
    http_session_cast(object, http) {
        return object.sendBodyBufferLength;
    }
}

void cq_http_send_body(cq_http *http, cq_bytes_in data, bool finish) {
    http_session_cast(object, http) {
        NSData *body = cq_oc_bytes(data);
        if (body != nil) {
            memcpy(object.sendBodyBuffer, body.bytes, body.length);
        }
        object.sendBodyFinish = finish;
    }
}

void cq_http_recv_body(cq_http *http, cq_bytes_out out) {
    http_session_cast(object, http) {
        cq_oc_set_bytes(object.receiveBodyData, out);
    }
}

void cq_http_recv_body_stop(cq_http *http, bool stop) {
    http_session_cast(object, http) {
        object.receiveBodyStop = stop;
    }
}

const char *cq_http_error(cq_http *http) {
    http_session_cast(object, http) {
        return cq_store_str(object.error.description.UTF8String);
    }
}

int32_t cq_http_recv_code(cq_http *http) {
    http_session_cast(object, http) {
        return (int32_t)object.responseCode;
    }
}

void cq_http_recv_header(cq_http *http, cq_ss_map_out out) {
    http_session_cast(object, http) {
        cq_oc_set_ss_map(object.responseHeader, out);
    }
}
