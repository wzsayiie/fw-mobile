#include "cqfoundationarche.h"
#include "cqwin32foundation.h"

//log:

void cq_log_info(const char *file, int32_t line, const char *message)
{
    cq_alloc_pool
    {
        LPCWSTR pszFile = cq_alloc_wstr(cq_wsfrom8s(file));
        LPCWSTR pszMessage = cq_alloc_wstr(cq_wsfrom8s(message));

        CQLogInfoW(pszFile, line, pszMessage);
    }
    cq_free_pool();
}

void cq_log_error(const char *file, int32_t line, const char *message)
{
    cq_alloc_pool
    {
        LPCWSTR pszFile = cq_alloc_wstr(cq_wsfrom8s(file));
        LPCWSTR pszMessage = cq_alloc_wstr(cq_wsfrom8s(message));

        CQLogErrorW(pszFile, line, pszMessage);
    }
    cq_free_pool();
}

//file management:

const char *cq_document_directory(void)
{
    LPCWSTR pszPath = CQDocumentDirectoryW();
    return cq_u8sfromws(pszPath);
}

const char *cq_caches_directory(void)
{
    LPCWSTR pszPath = CQCachesDirectoryW();
    return cq_u8sfromws(pszPath);
}

const char *cq_temporary_directory(void)
{
    LPCWSTR pszPath = CQTemporaryDirectoryW();
    return cq_u8sfromws(pszPath);
}

bool cq_directory_exists(const char *path)
{
    LPCWSTR pszPath = cq_wsfrom8s(path);
    return CQDirectoryExistsW(pszPath);
}

bool cq_file_exists(const char *path)
{
    LPCWSTR pszPath = cq_wsfrom8s(path);
    return CQFileExistsW(pszPath);
}

bool cq_create_directory(const char *path, bool intermediate)
{
    LPCWSTR pszPath = cq_wsfrom8s(path);
    return CQCreateDirectoryW(pszPath, intermediate);
}

void cq_remove_path(const char *path)
{
    LPCWSTR pszPath = cq_wsfrom8s(path);
    CQRemovePathW(pszPath);
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
