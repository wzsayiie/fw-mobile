#include "cqfoundationarche.h"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(PORT, "src/library/foundation/PORT");

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_log_info");
    method.fn<void>(file, line, message);
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_log_error");
    method.fn<void>(file, line, message);
}

//app bundle resource:

const char *cq_ios_bundle_path() {
    return nullptr;
}

const char *cq_ios_resource_path(const char *, const char *) {
    return nullptr;
}

void cq_ios_resource(const char *, const char *, cq_bytes_out) {
}

void cq_android_asset(const char *name, cq_bytes_out out) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_android_asset");
    method.fn<void>(name, out);
}

bool cq_android_copy_asset(const char *from_path, const char *to_path) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_android_copy_asset");
    return method.fn<bool>(from_path, to_path);
}

//file access:

const char *cq_document_directory() {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_document_directory");

    std::string ret = method.fn<std::string>();
    return cq_store_str(ret.data());
}

const char *cq_caches_directory() {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_caches_directory");

    std::string ret = method.fn<std::string>();
    return cq_store_str(ret.data());
}

const char *cq_temporary_directory() {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_temporary_directory");

    std::string ret = method.fn<std::string>();
    return cq_store_str(ret.data());
}

bool cq_directory_exists(const char *path) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_directory_exists");
    return method.fn<bool>(path);
}

bool cq_file_exists(const char *path) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_file_exists");
    return method.fn<bool>(path);
}

bool cq_create_directory(const char *path, bool intermediate) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_create_directory");
    return method.fn<bool>(path, intermediate);
}

void cq_remove_path(const char *path) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_remove_path");
    method.fn<void>(path);
}

void cq_sub_files(const char *path, cq_str_list_out out) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_sub_files");
    method.fn<void>(path, out);
}

//thread:

void cq_thread_run(cq_block *block) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_thread_run");
    method.fn<void>(block);
}

void cq_thread_sleep(float seconds) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_thread_sleep");
    method.fn<void>(seconds);
}

//main run loop:

void cq_main_loop_post(cq_block *block) {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_main_loop_post");
    method.fn<void>(block);
}

//http(s):

cq_http *cq_http_create() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_create");

    return method.call<cq_http *>();
}

void cq_http_timeout(cq_http *http, float seconds) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_timeout");

    method.push(http);
    method.push(seconds);

    method.callVoid();
}

void cq_http_send_method(cq_http *http, const char *httpMethod) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_send_method");

    method.push(http);
    method.push(httpMethod);

    method.callVoid();
}

void cq_http_send_url(cq_http *http, const char *url) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_send_url");

    method.push(http);
    method.push(url);

    method.callVoid();
}

void cq_http_send_query(cq_http *http, const char *field, const char *value) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_send_query");

    method.push(http);
    method.push(field);
    method.push(value);

    method.callVoid();
}

void cq_http_send_header(cq_http *http, const char *field, const char *value) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_send_header");

    method.push(http);
    method.push(field);
    method.push(value);

    method.callVoid();
}

void cq_http_sync(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_sync");

    method.push(http);

    method.callVoid();
}

int32_t cq_http_send_body_cap(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_send_body_cap");

    method.push(http);

    return method.callInt32();
}

void cq_http_send_body(cq_http *http, cq_bytes_in data, bool finish) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_send_body");

    method.push(http);
    method.push(data);
    method.push(finish);

    return method.callVoid();
}

void cq_http_recv_body(cq_http *http, cq_bytes_out out) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_recv_body");

    method.push(http);
    method.push(out);

    return method.callVoid();
}

void cq_http_recv_body_stop(cq_http *http, bool stop) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_recv_body_stop");

    method.push(http);
    method.push(stop);

    return method.callVoid();
}

const char *cq_http_error(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_error");

    method.push(http);

    std::string ret = method.callString();
    return cq_store_str(ret.c_str());
}

int32_t cq_http_recv_code(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_recv_code");

    method.push(http);

    return method.callInt32();
}

void cq_http_recv_header(cq_http *http, cq_ss_map_out out) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, "cq_http_recv_header");

    method.push(http);
    method.push(out);

    method.callVoid();
}
