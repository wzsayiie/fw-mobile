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
    cq_bytes *data = cq_ios_resource(name.c_str(), type.c_str());
    return cq_cpp_bytes_from(cq_c_bytes_sender, data);
}

cq_member(cqAndroidBundle) {
    std::vector<uint8_t> resourceBuffer;
};

cqAndroidBundleRef cqAndroidBundle::get() {
    return cqStaticObject<cqAndroidBundle>();
}

std::vector<uint8_t> cqAndroidBundle::asset(const std::string &name) {
    cq_bytes *data = cq_android_asset(name.c_str());
    return cq_cpp_bytes_from(cq_c_bytes_sender, data);
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
    if (cq_directory_exists(path.c_str())) {
        if (error != nullptr) {
            *error = true;
        }
        cq_strings *contents = cq_sub_files(path.c_str());
        return cq_cpp_strings_from(cq_c_strings_sender, contents);
    } else {
        if (error != nullptr) {
            *error = false;
        }
        return std::vector<std::string>();
    }
}

//thread:

static void cqThread_runnableBody(void *data) {
    auto ref = (std::function<void ()> *)data;
    (*ref)();
    delete ref;
}

void cqThread::run(std::function<void ()> task) {
    auto ref = new std::function<void ()>(task);
    cq_thread_run(cqThread_runnableBody, ref);
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

static void cqRunLoop_runnableBody(void *data) {
    auto ref = (std::function<void ()> *)data;
    (*ref)();
    delete ref;
}

void cqRunLoop::perform(std::function<void ()> task) {
    auto ref = new std::function<void ()>(task);
    cq_main_loop_post(cqRunLoop_runnableBody, ref);
}

//http(s):

cq_member(cqHTTPSession) {
    
    cq_http *http = nullptr;
    
    cqHTTPSession::RequestBodyReader requestBodyReader;
    std::vector<uint8_t> requestBodyData;
    size_t requestBodyDataCursor = 0;
    
    int responseCode = 0;
    std::map<std::string, std::string> responseHeader;
    cqHTTPSession::ResponseBodyWriter responseBodyWriter;
    std::vector<uint8_t> responseBodyData;
    
    std::string error;
};

cqHTTPSession::cqHTTPSession() {
    dat->http = cq_http_create();
}

cqHTTPSession::~cqHTTPSession() {
    cq_http_destroy(dat->http);
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

static int32_t cqHTTPSession_OnReadRequestBody(void *user, void *buffer, int32_t length) {
    auto session = (cqHTTPSession *)user;
    
    if (session->dat->requestBodyReader != nullptr) {
        return session->dat->requestBodyReader(buffer, length);
    }
    
    std::vector<uint8_t> &data = session->dat->requestBodyData;
    size_t &cursor = session->dat->requestBodyDataCursor;
    if (cursor < data.size()) {
        if (length > (int32_t)(data.size() - cursor)) {
            length = (int32_t)(data.size() - cursor);
        }
        memcpy(buffer, data.data() + cursor, length);
        cursor += length;
        return length;
    } else {
        return -1;
    }
}

static void cqHTTPSession_OnWriteResponseCode(void *user, int32_t code) {
    auto session = (cqHTTPSession *)user;
    
    session->dat->responseCode = code;
}

static void cqHTTPSession_OnWriteResponseHeader(void *user, const char *field, const char *value) {
    auto session = (cqHTTPSession *)user;
    
    if (!cq_str_empty(field) && !cq_str_empty(value)) {
        session->dat->responseHeader[field] = value;
    }
}

static bool cqHTTPSession_OnWriteResponseBody(void *user, const void *bytes, int32_t length) {
    auto session = (cqHTTPSession *)user;
    
    if (session->dat->responseBodyWriter != nullptr) {
        return session->dat->responseBodyWriter(bytes, length);
    } else {
        std::vector<uint8_t> &body = session->dat->responseBodyData;
        body.insert(body.end(), (uint8_t *)bytes, (uint8_t *)bytes + length);
        return true;
    }
}

void cqHTTPSession::syncResume() {
    
    //reset:
    cq_http_send_body_from(dat->http, cqHTTPSession_OnReadRequestBody    );
    cq_http_recv_code_to  (dat->http, cqHTTPSession_OnWriteResponseCode  );
    cq_http_recv_header_to(dat->http, cqHTTPSession_OnWriteResponseHeader);
    cq_http_recv_body_to  (dat->http, cqHTTPSession_OnWriteResponseBody  );
    
    dat->responseCode = 0;
    dat->responseHeader.clear();
    dat->responseBodyData.clear();
    dat->error.clear();
    
    //resume:
    cq_http_sync(dat->http, this);
    dat->error = cqString::make(cq_http_error(dat->http));
}

const std::string &cqHTTPSession::error() {
    return dat->error;
}

int cqHTTPSession::responseCode() {
    return dat->responseCode;
}

std::map<std::string, std::string> cqHTTPSession::responseHeader() {
    return dat->responseHeader;
}

void cqHTTPSession::setResponseBodyWriter(ResponseBodyWriter writer) {
    dat->responseBodyWriter = writer;
}

std::vector<uint8_t> cqHTTPSession::responseBodyData() {
    return dat->responseBodyData;
}
