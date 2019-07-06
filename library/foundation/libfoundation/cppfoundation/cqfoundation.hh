#pragma once

#include "cqcppbasis.hh"

#include "CQFOUNDATION_NS.hh"
_CQFOUNDATION_BEGIN_NS

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
    static std::string append(const std::string &parent, const std::string &child);
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

//network:

cq_class(cqURLSession, cqObject) {
    
    static cqURLSessionRef get();
    
    //NOTE:
    //android don't allow network operation on main thread.
    //on android, if the function called on main thread, always failed.
    virtual std::vector<char> sendSyncGet(const std::string &url, float timeout, int *outError);
};

_CQFOUNDATION_END_NS
