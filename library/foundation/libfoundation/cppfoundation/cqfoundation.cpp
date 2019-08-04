#include "cqfoundation.hh"
#include "cqfoundationarche.h"
#include <cstdarg>
#include <cstdio>

//log:

static void logging(
    decltype(cq_log_info) fn, const char *file, int line, const char *format, va_list args)
{
    if (format != nullptr) {
        char message[1024 * 4];
        vsnprintf(message, sizeof(message), format, args);
        fn(file, line, message);
    }
}

void cqLog::info(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    logging(cq_log_info, file, line, format, args);
    va_end(args);
}

void cqLog::error(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    logging(cq_log_error, file, line, format, args);
    va_end(args);
}

//file access:

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

cq_member(cqFileManager) {
};

cqFileManagerRef cqFileManager::get() {
    return cqStaticObject<cqFileManager>();
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
