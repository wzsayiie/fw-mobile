#include "cqfoundationarche.h"
#include "cqwin32foundation.h"

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
    LPWSTR pszFile = CQ_COPY_STR_W(cq_u16sfrom8s(file));
    LPWSTR pszMessage = CQ_COPY_STR_W(cq_u16sfrom8s(message));
    CQLogInfoW(pszFile, line, pszMessage);
    free(pszFile);
    free(pszMessage);
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    LPWSTR pszFile = CQ_COPY_STR_W(cq_u16sfrom8s(file));
    LPWSTR pszMessage = CQ_COPY_STR_W(cq_u16sfrom8s(message));
    CQLogErrorW(pszFile, line, pszMessage);
    free(pszFile);
    free(pszMessage);
}

//file management:

const char *cq_document_directory(void) {
    LPCWSTR a = CQDocumentDirectoryW();
    LPCWSTR b = CQ_STORE_STR_W(a);
    return cq_u8sfrom16s(b);
}

const char *cq_caches_directory(void) {
    LPCWSTR a = CQCachesDirectoryW();
    LPCWSTR b = CQ_STORE_STR_W(a);
    return cq_u8sfrom16s(b);
}

const char *cq_temporary_directory(void) {
    LPCWSTR a = CQTemporaryDirectoryW();
    LPCWSTR b = CQ_STORE_STR_W(a);
    return cq_u8sfrom16s(b);
}

bool cq_directory_exists(const char *path) {
    LPCWSTR pszPath = cq_u16sfrom8s(path);
    return CQDirectoryExistsW(pszPath);
}

bool cq_file_exists(const char *path) {
    LPCWSTR pszPath = cq_u16sfrom8s(path);
    return CQFileExistsW(pszPath);
}

bool cq_create_directory(const char *path, bool intermediate) {
    LPCWSTR pszPath = cq_u16sfrom8s(path);
    return CQCreateDirectoryW(pszPath, intermediate);
}

void cq_remove_path(const char *path) {
    LPCWSTR pszPath = cq_u16sfrom8s(path);
    CQRemovePathW(pszPath);
}

//thread:

void cq_thread_run(void (*task)(void *), void *data) {
    CQRunThread(task, data);
}

void cq_thread_sleep(float seconds) {
    CQThreadSleepSeconds(seconds);
}

//network:

int32_t cq_http_get(const char *url, float timeout) {
    return 1;
}

const void *cq_http_get_bytes(void) {
    return NULL;
}

int32_t cq_http_get_size(void) {
    return 0;
}
