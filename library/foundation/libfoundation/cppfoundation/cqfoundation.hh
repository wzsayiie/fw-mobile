#pragma once

#include "cqcppbasis.hh"

//log:

void cqLogInfo (const char *file, int line, const char *format, ...);
void cqLogError(const char *file, int line, const char *format, ...);

#define I(...) cqLogInfo (__FILE__, __LINE__, __VA_ARGS__)
#define E(...) cqLogError(__FILE__, __LINE__, __VA_ARGS__)

//file manager:

std::string cqDocumentDirectory();
std::string cqCachesDirectory();
std::string cqTemporaryDirectory();
std::string cqAppendPath(const std::string &parent, const std::string &child);

cq_class(cqFileManager, cqObject) {
    
    cqFileManager();
    
    static cqFileManagerRef get();
    
    virtual bool directoryExists(const std::string &path);
    virtual bool fileExists(const std::string &path);
    virtual bool createDirectory(const std::string &path, bool intermediate);
    virtual void removePath(const std::string &path);
};

//thread:

void cqThreadRun(std::function<void ()> task);
void cqThreadSleep(float seconds);

//net:

cq_class(cqURLSession, cqObject) {
    
    cqURLSession();
    
    static cqURLSessionRef get();
    
    virtual std::vector<char> sendSyncGet(const std::string &url, float timeout, int *outError);
};
