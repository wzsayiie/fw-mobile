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

//app bundle resource:

uint8_t *cq_bundle_res(int32_t *len, const char *type, const char *name) {
    //empty implementation.
    if (len != NULL) {
        *len = 0;
    }
    return nullptr;
}

//file access:

const char *cq_document_directory(void)
{
    std::string szPath = CQU8Str_From(CQDocumentDirectoryW());
    return cq_store_str(szPath.c_str());
}

const char *cq_caches_directory(void)
{
    std::string szPath = CQU8Str_From(CQTemporaryDirectoryW());
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

struct cq_http {

    CQHTTP *lpSession = NULL;

    cq_http_body_reader   fnRequestBodyReader    = NULL;
    cq_http_code_writer   fnResponseCodeWriter   = NULL;
    cq_http_header_writer fnResponseHeaderWriter = NULL;
    cq_http_body_writer   fnResponseBodyWriter   = NULL;

    VOID *lpUserData   = NULL;
    BOOL bWaitResponse = FALSE;
};

cq_http *cq_http_create()
{
    cq_http *http = new cq_http;
    http->lpSession = CQHttpCreate();
    return http;
}

void cq_http_destroy(cq_http *http)
{
    if (http != nullptr)
    {
        CQHttpDestroy(http->lpSession);
        delete http;
    }
}

void cq_http_timeout(cq_http *http, float seconds)
{
    if (http != nullptr)
    {
        CQHttpSetTimeout(http->lpSession, seconds);
    }
}

void cq_http_send_method(cq_http *http, const char *method)
{
    if (http != nullptr)
    {
        CQWSTR szMethod = CQWStr_FromU8S(method);
        CQHttpSetMethodW(http->lpSession, szMethod);
    }
}

void cq_http_send_url(cq_http *http, const char *url)
{
    if (http != nullptr)
    {
        CQWSTR szUrlString = CQWStr_FromU8S(url);
        CQHttpSetUrlStringW(http->lpSession, szUrlString);
    }
}

void cq_http_send_query(cq_http *http, const char *field, const char *value)
{
    if (http != nullptr)
    {
        CQWSTR szField = CQWStr_FromU8S(field);
        CQWSTR szValue = CQWStr_FromU8S(value);
        CQHttpSetUrlQueryW(http->lpSession, szField, szValue);
    }
}

void cq_http_send_header(cq_http *http, const char *field, const char *value)
{
    if (http != nullptr)
    {
        CQWSTR szField = CQWStr_FromU8S(field);
        CQWSTR szValue = CQWStr_FromU8S(value);
        CQHttpSetRequestHeaderW(http->lpSession, szField, szValue);
    }
}

void cq_http_send_body_from(cq_http *http, cq_http_body_reader reader)
{
    if (http != nullptr)
    {
        http->fnRequestBodyReader = reader;
    }
}

void cq_http_recv_code_to(cq_http *http, cq_http_code_writer writer)
{
    if (http != nullptr)
    {
        http->fnResponseCodeWriter = writer;
    }
}

void cq_http_recv_header_to(cq_http *http, cq_http_header_writer writer)
{
    if (http != nullptr)
    {
        http->fnResponseHeaderWriter = writer;
    }
}

void cq_http_recv_body_to(cq_http *http, cq_http_body_writer writer)
{
    if (http != nullptr)
    {
        http->fnResponseBodyWriter = writer;
    }
}

static int32_t cq_http_read_requst_body(cq_http *http, BYTE *buffer, int length)
{
    if (http->fnRequestBodyReader != NULL)
    {
        return http->fnRequestBodyReader(http->lpUserData, buffer, length);
    }
    else
    {
        return -1;
    }
}

static void cq_http_write_response_header(cq_http *http)
{
    if (http->fnResponseCodeWriter != NULL)
    {
        auto responseCode = (int32_t)CQHttpGetResponseCode(http->lpSession);
        http->fnResponseCodeWriter(http->lpUserData, responseCode);
    }
    if (http->fnResponseHeaderWriter != NULL)
    {
        for (auto &cp : CQHttpGetResponseHeaderW(http->lpSession))
        {
            std::string field = CQU8Str_From(cp.first);
            std::string value = CQU8Str_From(cp.second);
            http->fnResponseHeaderWriter(http->lpUserData, field.c_str(), value.c_str());
        }
    }
}

static bool cq_http_write_response_body(cq_http *http, CONST BYTE *bytes, int length)
{
    if (http->bWaitResponse)
    {
        cq_http_write_response_header(http);
        http->bWaitResponse = FALSE;
    }

    if (http->fnResponseBodyWriter != NULL)
    {
        return http->fnResponseBodyWriter(http->lpUserData, bytes, length);
    }
    else
    {
        return true;
    }
}

void cq_http_sync(cq_http *http, void *user)
{
    if (http == nullptr)
    {
        return;
    }

    http->lpUserData = user;
    http->bWaitResponse = TRUE;

    CQHttpSetRequestBodyReader(http->lpSession, [=](BYTE *buffer, int length) {
        return cq_http_read_requst_body(http, buffer, length);
    });
    CQhttpSetResponseBodyWriter(http->lpSession, [=](CONST BYTE *bytes, int length) {
        return cq_http_write_response_body(http, bytes, length);
    });

    CQHttpSyncResume(http->lpSession);
}

const char *cq_http_error(cq_http *http)
{
    if (http != nullptr)
    {
        std::string error = CQU8Str_From(CQHttpErrorW(http->lpSession));
        return cq_store_str(error.c_str());
    }
    else
    {
        return nullptr;
    }
}
