#include "cqfoundation.hh"
#include "cqfoundationarche.h"
#include <cstdarg>
#include <cstdio>

//log:

void cqLogInfo(const char *file, int line, const char *format, ...) {
    char message[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
    }
    cq_log_info(file, line, message);
}

void cqLogError(const char *file, int line, const char *format, ...) {
    char message[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
    }
    cq_log_error(file, line, message);
}

//file manager:

std::string cqDocumentDirectory() {
    const char *directory = cq_document_directory();
    return cqMakeString(directory);
}

std::string cqCachesDirectory() {
    const char *directory = cq_caches_directory();
    return cqMakeString(directory);
}

std::string cqTemporaryDirectory() {
    const char *directory = cq_temporary_directory();
    return cqMakeString(directory);
}

std::string cqAppendPath(const std::string &parent, const std::string &child) {
    const char *path = cq_append_path(parent.data(), child.data());
    return cqMakeString(path);
}

cq_member(cqFileManager) {
};

cqFileManager::cqFileManager() {
}

cqFileManagerRef cqFileManager::get() {
    static cqFileManagerRef object;
    if (object == nullptr) {
        object = cqFileManager::create();
    }
    return object;
}

bool cqFileManager::directoryExists(const std::string &path) {
    return cq_directory_exists(path.data());
}

bool cqFileManager::fileExists(const std::string &path) {
    return cq_file_exists(path.data());
}

bool cqFileManager::createDirectory(const std::string &path, bool intermediate) {
    return cq_create_directory(path.data(), intermediate);
}

void cqFileManager::removePath(const std::string &path) {
    cq_remove_path(path.data());
}
