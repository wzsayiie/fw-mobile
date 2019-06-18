#import "CQFoundation.h"
#import "cqfoundationarche.h"

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
    CQLogInfo(@(file), line, @"%s", message);
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    CQLogError(@(file), line, @"%s", message);
}

//file manager:

const char *cq_document_directory(void) {
    NSString *directory = CQDocumentDirectory();
    return cq_store_string(directory.UTF8String);
}

const char *cq_caches_directory(void) {
    NSString *directory = CQCachesDirectory();
    return cq_store_string(directory.UTF8String);
}

const char *cq_temporary_directory(void) {
    NSString *directory = CQTemporaryDirectory();
    return cq_store_string(directory.UTF8String);
}

const char *cq_append_path(const char *parent, const char *child) {
    NSString *path = CQAppendPath(@(parent), @(child));
    return cq_store_string(path.UTF8String);
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

//thread:

void cq_thread_run(void (*task)(void *), void *data) {
    if (task != NULL) {
        CQThreadRun(^{ task(data); });
    }
}

void cq_thread_sleep(float seconds) {
    CQThreadSleep(seconds);
}

//network:

static _Thread_local _cq_data _http_get = {NULL, 0};

int32_t cq_http_get(const char *url, float timeout) {
    NSError *error = nil;
    NSData *data = [CQURLSession.sharedObject sendSyncGet:@(url) timeout:timeout error:&error];
    if (error == nil) {
        _cq_assign_data(&_http_get, data.bytes, (int32_t)data.length);
        return 0;
    } else {
        _cq_assign_data(&_http_get, NULL, 0);
        return 1;
    }
}

const void *cq_http_get_bytes(void) {
    return _http_get.bytes;
}

int32_t cq_http_get_size(void) {
    return _http_get.size;
}
