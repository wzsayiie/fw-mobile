#include "cqfoundation.hh"
#include "cqfoundationarche.h"
#include <cstdarg>
#include <cstdio>

//log:

void cqLog::info(const char *file, int line, const char *format, ...) {
    char message[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
    }
    cq_log_info(file, line, message);
}

void cqLog::error(const char *file, int line, const char *format, ...) {
    char message[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
    }
    cq_log_error(file, line, message);
}

//file manager:

std::string cqPath::documentDirectory() {
    const char *directory = cq_document_directory();
    return cqString::make(directory);
}

std::string cqPath::cachesDirectory() {
    const char *directory = cq_caches_directory();
    return cqString::make(directory);
}

std::string cqPath::temporaryDirectory() {
    const char *directory = cq_temporary_directory();
    return cqString::make(directory);
}

std::string cqPath::append(const std::string &parent, const std::string &child) {
    const char *path = cq_append_path(parent.c_str(), child.c_str());
    return cqString::make(path);
}

cq_member(cqFileManager) {
};

cqFileManager::cqFileManager() {
}

cqFileManagerRef cqFileManager::get() {
    CQ_SYNCHRONIZE
    
    static cqFileManagerRef object;
    if (object == nullptr) {
        object = cqFileManager::create();
    }
    return object;
}

bool cqFileManager::directoryExists(const std::string &path) {
    return cq_directory_exists(path.c_str());
}

bool cqFileManager::fileExists(const std::string &path) {
    return cq_file_exists(path.c_str());
}

bool cqFileManager::createDirectory(const std::string &path, bool intermediate) {
    return cq_create_directory(path.c_str(), intermediate);
}

void cqFileManager::removePath(const std::string &path) {
    cq_remove_path(path.c_str());
}

//thread:

static void cqThreadBody(void *data) {
    auto ref = (std::function<void ()> *)data;
    (*ref)();
    delete ref;
}

void cqThread::run(std::function<void ()> task) {
    auto ref = new std::function<void ()>(task);
    cq_thread_run(cqThreadBody, ref);
}

void cqThread::sleep(float seconds) {
    cq_thread_sleep(seconds);
}

//network:

cq_member(cqURLSession) {
};

cqURLSession::cqURLSession() {
}

cqURLSessionRef cqURLSession::get() {
    CQ_SYNCHRONIZE
    
    static cqURLSessionRef object;
    if (object == nullptr) {
        object = cqURLSession::create();
    }
    return object;
}

std::vector<char> cqURLSession::sendSyncGet(const std::string &url, float timeout, int *outError) {
    int32_t error = cq_http_get(url.c_str(), timeout);
    if (outError != nullptr) {
        *outError = error;
    }
    
    std::vector<char> data;
    if (!error) {
        const void *bytes = cq_http_get_bytes();
        int32_t size = cq_http_get_size();
        data.resize(size);
        memcpy(&data[0], bytes, size);
    }
    return data;
}
