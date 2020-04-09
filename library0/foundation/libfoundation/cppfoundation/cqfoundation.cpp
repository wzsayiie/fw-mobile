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

void cqLog::info(const char *file, int line, _Printf_format_string_ const char *format, ...) {
    va_list args;
    va_start(args, format);
    logging(cq_log_info, file, line, format, args);
    va_end(args);
}

void cqLog::error(const char *file, int line, _Printf_format_string_ const char *format, ...) {
    va_list args;
    va_start(args, format);
    logging(cq_log_error, file, line, format, args);
    va_end(args);
}

//app bundle resource:

cq_member(cqIOSBundle) {
    std::vector<uint8_t> resourceBuffer;
};

cqIOSBundleRef cqIOSBundle::get() {
    return cqStaticObject<cqIOSBundle>();
}

std::string cqIOSBundle::bundlePath() {
    const char *path = cq_ios_bundle_path();
    return cqString::make(path);
}

std::string cqIOSBundle::resourcePath(const std::string &name, const std::string &type) {
    const char *path = cq_ios_resource_path(name.c_str(), type.c_str());
    return cqString::make(path);
}

std::vector<uint8_t> cqIOSBundle::resource(const std::string &name, const std::string &type) {
    std::vector<uint8_t> data;
    cq_ios_resource(name.c_str(), type.c_str(), cq_cpp_out(data));
    return data;
}

cq_member(cqAndroidBundle) {
    std::vector<uint8_t> resourceBuffer;
};

cqAndroidBundleRef cqAndroidBundle::get() {
    return cqStaticObject<cqAndroidBundle>();
}

std::vector<uint8_t> cqAndroidBundle::asset(const std::string &name) {
    std::vector<uint8_t> data;
    cq_android_asset(name.c_str(), cq_cpp_out(data));
    return data;
}

bool cqAndroidBundle::copyAsset(const std::string &fromPath, const std::string &toPath) {
    return cq_android_copy_asset(fromPath.c_str(), toPath.c_str());
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

std::vector<std::string> cqFileManager::contentsOfDirectoryAtPath(const std::string &path, bool *error) {
    std::vector<std::string> contents;
    
    if (cq_directory_exists(path.c_str())) {
        if (error != nullptr) {
            *error = true;
        }
        cq_sub_files(path.c_str(), cq_cpp_out(contents));
    } else {
        if (error != nullptr) {
            *error = false;
        }
    }
    
    return contents;
}

//thread:

static void cqThread_block(void *data) {
    auto ref = (std::function<void ()> *)data;
    (*ref)();
    delete ref;
}

void cqThread::run(std::function<void ()> task) {
    auto ref = new std::function<void ()>(task);
    cq_thread_run(cqThread_block, ref);
}

void cqThread::sleep(float seconds) {
    cq_thread_sleep(seconds);
}

//main run loop:

cq_member(cqRunLoop) {
};

cqRunLoopRef cqRunLoop::mainRunLoop() {
    return cqStaticObject<cqRunLoop>();
}

static void cqRunLoop_block(void *data) {
    auto ref = (std::function<void ()> *)data;
    (*ref)();
    delete ref;
}

void cqRunLoop::perform(std::function<void ()> task) {
    auto ref = new std::function<void ()>(task);
    cq_main_loop_post(cqRunLoop_block, ref);
}

//http(s):

cq_member(cqHTTPSession) {
    
    cq_http *http = nullptr;
    
    cqHTTPSession::RequestBodyReader requestBodyReader;
    std::vector<uint8_t> requestBodyData;
    size_t requestBodyDataCursor = 0;
    
    cqHTTPSession::ResponseBodyWriter responseBodyWriter;
    std::vector<uint8_t> responseBodyData;
};

cqHTTPSession::cqHTTPSession() {
    dat->http = cq_http_create();
}

cqHTTPSession::~cqHTTPSession() {
    cq_http_release(dat->http);
}

void cqHTTPSession::setTimeout(float seconds) {
    cq_http_timeout(dat->http, seconds);
}

void cqHTTPSession::setMethod(const std::string &method) {
    cq_http_send_method(dat->http, method.c_str());
}

void cqHTTPSession::setURLString(const std::string &urlString) {
    cq_http_send_url(dat->http, urlString.c_str());
}

void cqHTTPSession::setURLQuery(const std::string &field, const std::string &value) {
    cq_http_send_query(dat->http, field.c_str(), value.c_str());
}

void cqHTTPSession::setRequestHeader(const std::string &field, const std::string &value) {
    cq_http_send_header(dat->http, field.c_str(), value.c_str());
}

void cqHTTPSession::setRequestBodyReader(RequestBodyReader reader) {
    dat->requestBodyReader = reader;
}

void cqHTTPSession::setRequestBodyData(const std::vector<uint8_t> &data) {
    dat->requestBodyData = data;
    dat->requestBodyDataCursor = 0;
}

static void cqHTTPSession_OnSendRequestBody(void *_self) {
    auto self = (cqHTTPSession *)_self;
    
    int32_t capacity = cq_cpp_block_int32("capacity");
    std::vector<uint8_t> buffer(capacity);
    
    if (self->dat->requestBodyReader != nullptr) {
        int length = self->dat->requestBodyReader(buffer.data(), capacity);
        if (length > 0) {
            buffer.resize(length);
            cq_cpp_block_set("buffer", buffer);
        }
        
        if (length == -1) {
            //NOTE: -1 means stop transfer.
            cq_cpp_block_set("stop", true);
        }
        
    } else {
        std::vector<uint8_t> &data = self->dat->responseBodyData;
        size_t &cursor = self->dat->requestBodyDataCursor;
        
        if (cursor < data.size()) {
            size_t length = std::min(data.size() - cursor, (size_t)capacity);
            
            buffer.assign(data.begin(), data.begin() + length);
            cq_cpp_block_set("buffer", buffer);
            
            cursor += length;
            
        } else {
            cq_cpp_block_set("stop", true);
        }
    }
}

static void cqHTTPSession_OnReceiveResponseBody(void *_self) {
    auto self = (cqHTTPSession *)_self;
    
    std::vector<uint8_t> body = cq_cpp_block_bytes("body");
    
    if (self->dat->responseBodyWriter != nullptr) {
        bool continuous = self->dat->responseBodyWriter(body);
        if (!continuous) {
            cq_cpp_block_set("stop", true);
        }
        
    } else {
        std::vector<uint8_t> &data = self->dat->responseBodyData;
        data.insert(data.end(), body.begin(), body.end());
    }
}

void cqHTTPSession::syncResume() {
    
    //reset:
    cq_http_listen_event(dat->http, cq_http_e_send_body, cqHTTPSession_OnSendRequestBody    , this);
    cq_http_listen_event(dat->http, cq_http_e_recv_body, cqHTTPSession_OnReceiveResponseBody, this);
    
    dat->responseBodyData.clear();
    
    //resume:
    cq_http_sync(dat->http);
}

std::string cqHTTPSession::error() {
    const char *error = cq_http_error(dat->http);
    return cqString::make(error);
}

int cqHTTPSession::responseCode() {
    return cq_http_recv_code(dat->http);
}

std::map<std::string, std::string> cqHTTPSession::responseHeader() {
    std::map<std::string, std::string> header;
    cq_http_recv_header(dat->http, cq_cpp_out(header));
    return header;
}

void cqHTTPSession::setResponseBodyWriter(ResponseBodyWriter writer) {
    dat->responseBodyWriter = writer;
}

std::vector<uint8_t> cqHTTPSession::responseBodyData() {
    return dat->responseBodyData;
}
