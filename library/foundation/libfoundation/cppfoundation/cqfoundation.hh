#pragma once

#include "cqcppbasis.hh"

#include "_CQFOUNDATION_VERSION.h"
_CQFOUNDATION_BEGIN_VERSION_NS

//log:

struct cqLog {
    static void info (const char *file, int line, const char *format, ...);
    static void error(const char *file, int line, const char *format, ...);
};

#define I(...) cqLog::info (__FILE__, __LINE__, __VA_ARGS__)
#define E(...) cqLog::error(__FILE__, __LINE__, __VA_ARGS__)

//file manager:

struct cqPath {
    static std::string documentDirectory();
    static std::string cachesDirectory();
    static std::string temporaryDirectory();
};

cq_class(cqFileManager, cqObject) {
    
    static cqFileManagerRef get();
    
    virtual bool directoryExists(const std::string &path);
    virtual bool fileExists(const std::string &path);
    virtual bool createDirectory(const std::string &path, bool intermediate);
    virtual void removePath(const std::string &path);
};

//thread:

struct cqThread {
    static void run(std::function<void ()> task);
    static void sleep(float seconds);
};

_CQFOUNDATION_END_VERSION_NS
