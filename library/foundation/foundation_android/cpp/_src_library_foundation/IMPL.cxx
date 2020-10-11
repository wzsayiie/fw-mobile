#include "cqfoundationintf.h"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(PORT, "src/library/foundation/IMPL");

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(file, line, message);
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(file, line, message);
}

//app bundle resource:

const char *cq_ios_bundle_path() {
    return nullptr;
}

const char *cq_ios_resource_path(const char *, const char *) {
    return nullptr;
}

void cq_ios_resource(const char *, const char *, cq_bytes *) {
}

void cq_android_asset(const char *name, cq_bytes *out) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(name, out);
}

bool cq_android_copy_asset(const char *from_path, const char *to_path) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    return method.fn<bool>(from_path, to_path);
}

//file access:

const char *cq_document_directory() {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);

    std::string ret = method.fn<std::string>();
    return cq_str_store(ret.data());
}

const char *cq_caches_directory() {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);

    std::string ret = method.fn<std::string>();
    return cq_str_store(ret.data());
}

const char *cq_temporary_directory() {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);

    std::string ret = method.fn<std::string>();
    return cq_str_store(ret.data());
}

bool cq_directory_exists(const char *path) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    return method.fn<bool>(path);
}

bool cq_file_exists(const char *path) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    return method.fn<bool>(path);
}

bool cq_create_directory(const char *path, bool intermediate) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    return method.fn<bool>(path, intermediate);
}

void cq_remove_path(const char *path) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(path);
}

void cq_sub_files(const char *path, cq_str_list *out) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(path, out);
}

//thread:

void cq_thread_run(cq_block *block) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(block);
}

void cq_thread_sleep(float seconds) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(seconds);
}

//main run loop:

void cq_main_loop_post(cq_block *block) {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>(block);
}

//http(s):

cq_http *cq_http_create() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    return method.call<cq_http *>();
}

void cq_http_timeout(cq_http *http, float seconds) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(seconds);

    method.callVoid();
}

void cq_http_send_method(cq_http *http, const char *httpMethod) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(httpMethod);

    method.callVoid();
}

void cq_http_send_url(cq_http *http, const char *url) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(url);

    method.callVoid();
}

void cq_http_send_query(cq_http *http, const char *field, const char *value) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(field);
    method.push(value);

    method.callVoid();
}

void cq_http_send_header(cq_http *http, const char *field, const char *value) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(field);
    method.push(value);

    method.callVoid();
}

void cq_http_sync(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);

    method.callVoid();
}

int32_t cq_http_send_body_cap(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);

    return method.callInt32();
}

void cq_http_send_body(cq_http *http, cq_bytes *data, bool finish) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(data);
    method.push(finish);

    return method.callVoid();
}

void cq_http_recv_body(cq_http *http, cq_bytes *out) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(out);

    return method.callVoid();
}

void cq_http_recv_body_stop(cq_http *http, bool stop) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(stop);

    return method.callVoid();
}

const char *cq_http_error(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);

    std::string ret = method.callString();
    return cq_str_store(ret.c_str());
}

int32_t cq_http_recv_code(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);

    return method.callInt32();
}

void cq_http_recv_header(cq_http *http, cq_ss_map *out) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(PORT(), &methodID, __func__);

    method.push(http);
    method.push(out);

    method.callVoid();
}
