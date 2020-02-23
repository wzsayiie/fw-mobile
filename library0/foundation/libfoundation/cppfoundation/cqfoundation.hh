#pragma once

#include "cqcppbasis.hh"

# ifdef __GNUC__
#   include <sys/cdefs.h>
#   define _Printf_format_string_
# else
#   include <sal.h>
#   define __printflike(format, args)
# endif

#include "_CQFOUNDATION_VERSION.h"
_CQFOUNDATION_BEGIN_VERSION_NS

//log:

struct cqLog {
    
    static void info(const char *file, int line,
        _Printf_format_string_ const char *format, ...) __printflike(3, 4);
    
    static void error(const char *file, int line,
        _Printf_format_string_ const char *format, ...) __printflike(3, 4);
};

#define I(...) cqLog::info (__FILE__, __LINE__, __VA_ARGS__)
#define E(...) cqLog::error(__FILE__, __LINE__, __VA_ARGS__)

//app bundle resource:

cq_class(cqIOSBundle, cqObject) {
    
    static cqIOSBundleRef get();
    
    virtual std::string bundlePath();
    virtual std::string resourcePath(const std::string &name, const std::string &type);
    virtual std::vector<uint8_t> resource(const std::string &name, const std::string &type);
};

cq_class(cqAndroidBundle, cqObject) {
    
    static cqAndroidBundleRef get();
    
    virtual std::vector<uint8_t> asset(const std::string &name);
    virtual bool copyAsset(const std::string &fromPath, const std::string &toPath);
};

//file access:

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
    virtual std::vector<std::string> contentsOfDirectoryAtPath(const std::string &path, bool *error);
};

//thread:

struct cqThread {
    static void run(std::function<void ()> task);
    static void sleep(float seconds);
};

//main run loop:

cq_class(cqRunLoop, cqObject) {
    
    static cqRunLoopRef mainRunLoop();
    
    virtual void perform(std::function<void ()> task);
};

//http(s):

cq_class(cqHTTPSession, cqObject) {
    
    cqHTTPSession();
    virtual ~cqHTTPSession();
    
    virtual void setTimeout(float seconds);
    virtual void setMethod(const std::string &method);
    virtual void setURLString(const std::string &urlString);
    
    //cqHTTPSession will perform the percent escape on its own.
    virtual void setURLQuery(const std::string &field, const std::string &value);
    
    virtual void setRequestHeader(const std::string &field, const std::string &value);
    
    typedef std::function<int (void *buffer, int length)> RequestBodyReader;
    
    //if set a RequestBodyReader, the session will use it to get request body,
    //else the request body from value set by setRequestBodyData().
    virtual void setRequestBodyReader(RequestBodyReader reader);
    virtual void setRequestBodyData(const std::vector<uint8_t> &data);
    
    virtual void syncResume();
    virtual const std::string &error();
    
    virtual int responseCode();
    virtual std::map<std::string, std::string> responseHeader();
    
    typedef std::function<bool (const void *bytes, int length)> ResponseBodyWriter;
    
    //if set a ResponseBodyWriter, the session will use it to write response body,
    //else the response body stored into internal data, which can be get by responseBodyData().
    virtual void setResponseBodyWriter(ResponseBodyWriter writer);
    virtual std::vector<uint8_t> responseBodyData();
};

_CQFOUNDATION_END_VERSION_NS
