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

@interface CQHTTPSessionBridge : CQHTTPSession <CQHTTPSessionDelegate>
@property (nonatomic) cq_http *intf;
@end

@implementation CQHTTPSessionBridge

- (NSInteger)HTTPSession:(CQHTTPSession *)session
   requestBodyFromBuffer:(void *)buffer
            bufferLength:(NSInteger)bufferLength
{
    NSMutableData *bufferObject = [NSMutableData data];
    BOOL stop = NO;
    
    cq_oc_block_bytes_out(@"buffer", bufferObject);
    cq_oc_block_int32_in(@"capacity", (int32_t)bufferLength);
    cq_oc_block_bool_out(@"stop", &stop);
    cq_http_emit_event(self.intf, cq_http_e_send_body);
    
    if (bufferObject.length > 0) {
        memcpy(buffer, bufferObject.bytes, bufferObject.length);
    }
    
    if (!stop) {
        return bufferObject.length;
    } else {
        return -1;
    }
}

- (BOOL)HTTPSession:(CQHTTPSession *)session responseBodyData:(NSData *)data {
    BOOL stop = NO;
    
    cq_oc_block_bytes_in(@"body", data);
    cq_oc_block_bool_out(@"stop", &stop);
    cq_http_emit_event(self.intf, cq_http_e_recv_body);
    
    if (!stop) {
        return YES;
    } else {
        return NO;
    }
}

@end

cq_http *cq_http_create(void) {
    CQHTTPSessionBridge *object = [[CQHTTPSessionBridge alloc] init];
    cq_http *intf = cq_obj_retain_oc(object, @"HTTPSession");
    
    object.intf = intf;
    
    return intf;
}

#define http_session_bridge(OBJECT, INTF)\
/**/    CQHTTPSessionBridge *OBJECT = cq_obj_raw_oc(INTF, CQHTTPSessionBridge.class);\

void cq_http_timeout(cq_http *http, float seconds) {
    http_session_bridge(object, http) {
        object.timeoutSeconds = seconds;
    }
}

void cq_http_send_method(cq_http *http, const char *method) {
    http_session_bridge(object, http) {
        object.method = CQNullableString(method);
    }
}

void cq_http_send_url(cq_http *http, const char *url) {
    http_session_bridge(object, http) {
        object.URLString = CQNullableString(url);
    }
}

void cq_http_send_query(cq_http *http, const char *field, const char *value) {
    http_session_bridge(object, http) {
        if (cq_str_empty(field)) {return;}
        if (cq_str_empty(value)) {return;}
        
        [object setURLQueryField:@(field) value:@(value)];
    }
}

void cq_http_send_header(cq_http *http, const char *field, const char *value) {
    http_session_bridge(object, http) {
        if (cq_str_empty(field)) {return;}
        if (cq_str_empty(value)) {return;}
        
        [object setRequestHeaderField:@(field) value:@(value)];
    }
}

void cq_http_sync(cq_http *http) {
    http_session_bridge(object, http) {
        [object syncResume];
    }
}

const char *cq_http_error(cq_http *http) {
    http_session_bridge(object, http) {
        return cq_store_str(object.error.description.UTF8String);
    }
}

int32_t cq_http_recv_code(cq_http *http) {
    http_session_bridge(object, http) {
        return (int32_t)object.responseCode;
    }
}

void cq_http_recv_header(cq_http *http, cq_ss_map_out out) {
    http_session_bridge(object, http) {
        cq_oc_set_ss_map(object.responseHeader, out);
    }
}
