#include "cqfoundationarche.h"
#include "cqwin32foundation.hh"

//log:

void cq_log_info(const char *file, int32_t line, const char *message)
{
    CQWSTR szFile = CQWStr_FromU8S(file);
    CQWSTR szMessage = CQWStr_FromU8S(message);

    CQLogInfoW(szFile.c_str(), line, szMessage.c_str());
}

void cq_log_error(const char *file, int32_t line, const char *message)
{
    CQWSTR szFile = CQWStr_FromU8S(file);
    CQWSTR szMessage = CQWStr_FromU8S(message);

    CQLogErrorW(szFile.c_str(), line, szMessage.c_str());
}

//file access:

const char *cq_document_directory(void)
{
    std::string szPath = CQU8Str_From(CQDocumentDirectoryW());
    return cq_store_str(szPath.c_str());
}

const char *cq_caches_directory(void)
{
    std::string szPath = CQU8Str_From(CQCachesDirectoryW());
    return cq_store_str(szPath.c_str());
}

const char *cq_temporary_directory(void)
{
    std::string szPath = CQU8Str_From(CQTemporaryDirectoryW());
    return cq_store_str(szPath.c_str());
}

bool cq_directory_exists(const char *path)
{
    CQWSTR szPath = CQWStr_FromU8S(path);
    return CQDirectoryExistsW(szPath);
}

bool cq_file_exists(const char *path)
{
    CQWSTR szPath = CQWStr_FromU8S(path);
    return CQFileExistsW(szPath);
}

bool cq_create_directory(const char *path, bool intermediate)
{
    CQWSTR szPath = CQWStr_FromU8S(path);
    return CQCreateDirectoryW(szPath, intermediate);
}

void cq_remove_path(const char *path)
{
    CQWSTR szPath = CQWStr_FromU8S(path);
    CQRemovePathW(szPath);
}

//thread:

void cq_thread_run(void (*task)(void *), void *data)
{
    if (task != nullptr)
    {
        CQRunThread([=]() { task(data); });
    }
}

void cq_thread_sleep(float seconds)
{
    CQThreadSleepSeconds(seconds);
}

//http(s):

cq_http *cq_http_create()
{
    return NULL;
}

void cq_http_destroy(cq_http *http)
{
}

void cq_http_timeout(cq_http *http, float seconds)
{
}

void cq_http_send_method(cq_http *http, const char *method)
{
}

void cq_http_send_url(cq_http *http, const char *url)
{
}

void cq_http_send_query(cq_http *http, const char *field, const char *value)
{
}

void cq_http_send_header(cq_http *http, const char *field, const char *value)
{
}

void cq_http_send_body_from(cq_http *http, cq_http_body_reader reader)
{
}

void cq_http_recv_code_to(cq_http *http, cq_http_code_writer writer)
{
}

void cq_http_recv_header_to(cq_http *http, cq_http_header_writer writer)
{
}

void cq_http_recv_body_to(cq_http *http, cq_http_body_writer writer)
{
}

void cq_http_sync(cq_http *http, void *user)
{
}

const char *cq_http_error(cq_http *http)
{
    return NULL;
}
