#include "cqfoundationarche.h"
#include "cqwin32foundation.h"

//log:

void cq_log_info(const char *file, int32_t line, const char *message)
{
    cq_malloc_pool
    {
        LPCWSTR a = cq_push_wstr cq_wsfrom8s(file);
        int     b = line;
        LPCWSTR c = cq_push_wstr cq_wsfrom8s(message);

        CQLogInfoW(a, b, c);
    }
    cq_free_pool();
}

void cq_log_error(const char *file, int32_t line, const char *message)
{
    cq_malloc_pool
    {
        LPCWSTR a = cq_push_wstr cq_wsfrom8s(file);
        int     b = line;
        LPCWSTR c = cq_push_wstr cq_wsfrom8s(message);

        CQLogErrorW(a, b, c);
    }
    cq_free_pool();
}

//file management:

const char *cq_document_directory(void)
{
    LPCWSTR z = CQDocumentDirectoryW();
    return cq_u8sfromws(z);
}

const char *cq_caches_directory(void)
{
    LPCWSTR z = CQCachesDirectoryW();
    return cq_u8sfromws(z);
}

const char *cq_temporary_directory(void)
{
    LPCWSTR z = CQTemporaryDirectoryW();
    return cq_u8sfromws(z);
}

bool cq_directory_exists(const char *path)
{
    LPCWSTR a = cq_wsfrom8s(path);
    return CQDirectoryExistsW(a);
}

bool cq_file_exists(const char *path)
{
    LPCWSTR a = cq_wsfrom8s(path);
    return CQFileExistsW(a);
}

bool cq_create_directory(const char *path, bool intermediate)
{
    LPCWSTR a = cq_wsfrom8s(path);
    BOOL    b = intermediate;

    return CQCreateDirectoryW(a, b);
}

void cq_remove_path(const char *path)
{
    LPCWSTR a = cq_wsfrom8s(path);
    CQRemovePathW(a);
}

//thread:

void cq_thread_run(void (*task)(void *), void *data)
{
    CQRunThread(task, data);
}

void cq_thread_sleep(float seconds)
{
    CQThreadSleepSeconds(seconds);
}
