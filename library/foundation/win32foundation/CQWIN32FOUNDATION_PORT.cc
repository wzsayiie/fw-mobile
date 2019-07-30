#include "cqfoundationarche.h"
#include "cqwin32foundation.hh"

//log:

void cq_log_info(const char *file, int32_t line, const char *message)
{
    CQWSTR szFile = CQWString::FromU8S(file);
    CQWSTR szMessage = CQWString::FromU8S(message);

    CQLogInfoW(szFile.c_str(), line, szMessage.c_str());
}

void cq_log_error(const char *file, int32_t line, const char *message)
{
    CQWSTR szFile = CQWString::FromU8S(file);
    CQWSTR szMessage = CQWString::FromU8S(message);

    CQLogErrorW(szFile.c_str(), line, szMessage.c_str());
}

//file management:

const char *cq_document_directory(void)
{
    std::string szPath = CQU8String::From(CQDocumentDirectoryW());
    return cq_store_u8str(szPath.c_str());
}

const char *cq_caches_directory(void)
{
    std::string szPath = CQU8String::From(CQCachesDirectoryW());
    return cq_store_u8str(szPath.c_str());
}

const char *cq_temporary_directory(void)
{
    std::string szPath = CQU8String::From(CQTemporaryDirectoryW());
    return cq_store_u8str(szPath.c_str());
}

bool cq_directory_exists(const char *path)
{
    CQWSTR szPath = CQWString::FromU8S(path);
    return CQDirectoryExistsW(szPath);
}

bool cq_file_exists(const char *path)
{
    CQWSTR szPath = CQWString::FromU8S(path);
    return CQFileExistsW(szPath);
}

bool cq_create_directory(const char *path, bool intermediate)
{
    CQWSTR szPath = CQWString::FromU8S(path);
    return CQCreateDirectoryW(szPath, intermediate);
}

void cq_remove_path(const char *path)
{
    CQWSTR szPath = CQWString::FromU8S(path);
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
