#include "cqfoundationarche.h"

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
}

void cq_log_error(const char *file, int32_t line, const char *message) {
}

//file manager:

const char *cq_document_directory(void) {
    return nullptr;
}

const char *cq_caches_directory(void) {
    return nullptr;
}

const char *cq_temporary_directory(void) {
    return nullptr;
}

const char *cq_append_path(const char *parent, const char *child) {
    return nullptr;
}

bool cq_directory_exists(const char *path) {
    return false;
}

bool cq_file_exists(const char *path) {
    return false;
}

bool cq_create_directory(const char *path, bool intermediate) {
    return false;
}

void cq_remove_path(const char *path) {
}

//thread:

void cq_thread_run(void (*task)(void *), void *data) {
}

void cq_thread_sleep(float seconds) {
}

//network:

static thread_local struct _cq_data _http_get = {NULL, 0};

int32_t cq_http_get(const char *url, float timeout) {
    return 1;
}

const void *cq_http_get_bytes(void) {
    return _http_get.bytes;
}

int32_t cq_http_get_size(void) {
    return _http_get.size;
}
