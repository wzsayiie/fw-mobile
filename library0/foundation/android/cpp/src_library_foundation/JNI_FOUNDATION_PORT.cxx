#include "cqfoundationarche.h"
#include "cqjnihelper.hh"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/foundation/PORT");
    }
    return clazz;
}

//log:

void cq_log_info(const char *file, int32_t line, const char *message) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_log_info");

    method.push(file);
    method.push(line);
    method.push(message);

    method.callVoid();
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_log_error");

    method.push(file);
    method.push(line);
    method.push(message);

    method.callVoid();
}

//app bundle resource:

const char *cq_ios_bundle_path() {
    return nullptr;
}

const char *cq_ios_bundle_res_path(const char *, const char *) {
    return nullptr;
}

void cq_ios_bundle_res_to(cq_ios_bundle_res_writer, void *, const char *, const char *) {
}

void cq_andr_asset_to(cq_andr_asset_writer writer, void *user, const char *name) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_andr_asset_to");

    method.push((jlong)writer);
    method.push((jlong)user);
    method.push(name);

    method.callVoid();
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_bundleWriteAsset
    (JNIEnv *env, jclass, jlong _writer, jlong userData, jbyteArray _asset)
{
    auto writer = (cq_andr_asset_writer)_writer;
    cqJNIByteArrayHelper asset(env, _asset);

    writer((void *)userData, asset.bytes(), asset.length());
}

bool cq_andr_copy_asset(const char *from_path, const char *to_path) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_andr_copy_asset");

    method.push(from_path);
    method.push(to_path);

    return method.callBool();
}

//file access:

const char *cq_document_directory() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_document_directory");

    std::string ret = method.callString();
    return cq_store_str(ret.data());
}

const char *cq_caches_directory() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_caches_directory");

    std::string ret = method.callString();
    return cq_store_str(ret.data());
}

const char *cq_temporary_directory() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_temporary_directory");

    std::string ret = method.callString();
    return cq_store_str(ret.data());
}

bool cq_directory_exists(const char *path) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_directory_exists");

    method.push(path);

    return method.callBool();
}

bool cq_file_exists(const char *path) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_file_exists");

    method.push(path);

    return method.callBool();
}

bool cq_create_directory(const char *path, bool intermediate) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_create_directory");

    method.push(path);
    method.push(intermediate);

    return method.callBool();
}

void cq_remove_path(const char *path) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_remove_path");

    method.push(path);

    method.callVoid();
}

bool cq_open_dir(const char *path) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_open_dir");

    method.push(path);

    return method.callBool();
}

const char *cq_read_dir() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_read_dir");

    std::string ret = method.callString();
    return cq_store_str(ret.c_str());
}

void cq_close_dir() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_close_dir");

    method.callVoid();
}

//thread:

void cq_thread_run(void (*task)(void *), void *data) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_thread_run");

    method.push((jlong)task);
    method.push((jlong)data);

    method.callVoid();
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_threadBody
    (JNIEnv *, jclass, jlong _task, jlong _data)
{
    auto task = (void (*)(void *))_task;
    auto data = (void *)_data;
    task(data);
}

void cq_thread_sleep(float seconds) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_thread_sleep");

    method.push(seconds);

    method.callVoid();
}

//http(s):

cq_http *cq_http_create() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_create");

    return (cq_http *)method.callInt64();
}

void cq_http_destroy(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_destroy");

    method.push((jlong)http);

    method.callVoid();
}

void cq_http_timeout(cq_http *http, float seconds) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_timeout");

    method.push((jlong)http);
    method.push(seconds);

    method.callVoid();
}

void cq_http_send_method(cq_http *http, const char *httpMethod) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_send_method");

    method.push((jlong)http);
    method.push(httpMethod);

    method.callVoid();
}

void cq_http_send_url(cq_http *http, const char *url) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_send_url");

    method.push((jlong)http);
    method.push(url);

    method.callVoid();
}

void cq_http_send_query(cq_http *http, const char *field, const char *value) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_send_query");

    method.push((jlong)http);
    method.push(field);
    method.push(value);

    method.callVoid();
}

void cq_http_send_header(cq_http *http, const char *field, const char *value) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_send_header");

    method.push((jlong)http);
    method.push(field);
    method.push(value);

    method.callVoid();
}

void cq_http_send_body_from(cq_http *http, cq_http_body_reader reader) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_send_body_from");

    method.push((jlong)http);
    method.push((jlong)reader);

    method.callVoid();
}

void cq_http_recv_code_to(cq_http *http, cq_http_code_writer writer) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_recv_code_to");

    method.push((jlong)http);
    method.push((jlong)writer);

    method.callVoid();
}

void cq_http_recv_header_to(cq_http *http, cq_http_header_writer writer) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_recv_header_to");

    method.push((jlong)http);
    method.push((jlong)writer);

    method.callVoid();
}

void cq_http_recv_body_to(cq_http *http, cq_http_body_writer writer) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_recv_body_to");

    method.push((jlong)http);
    method.push((jlong)writer);

    method.callVoid();
}

void cq_http_sync(cq_http *http, void *user) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_sync");

    method.push((jlong)http);
    method.push((jlong)user);

    method.callVoid();
}

const char *cq_http_error(cq_http *http) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_http_error");

    method.push((jlong)http);

    std::string ret = method.callString();
    return cq_store_str(ret.c_str());
}

extern "C" JNIEXPORT jint JNICALL Java_src_library_foundation_PORT_httpReadRequestBody
    (JNIEnv *env, jclass, jlong _reader, jlong userData, jbyteArray _buffer)
{
    auto reader = (cq_http_body_reader)_reader;
    cqJNIByteArrayHelper buffer(env, _buffer);

    std::vector<jbyte> data((size_t)buffer.length());
    int32_t readLen = reader((void *)userData, data.data(), (int32_t)data.size());

    if (readLen > 0) {
        buffer.write(0, data.data(), readLen);
    }
    return readLen;
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_httpWriteResponseCode
    (JNIEnv *, jclass, jlong _writer, jlong userData, jint responseCode)
{
    auto writer = (cq_http_code_writer)_writer;
    writer((void *)userData, (int32_t)responseCode);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_httpWriteResponseHeader
    (JNIEnv *env, jclass, jlong _writer, jlong userData, jstring _field, jstring _value)
{
    auto writer = (cq_http_header_writer)_writer;
    std::string field = cqJNIU8StringFromJNI(env, _field);
    std::string value = cqJNIU8StringFromJNI(env, _value);

    writer((void *)userData, field.c_str(), value.c_str());
}

extern "C" JNIEXPORT jboolean JNICALL Java_src_library_foundation_PORT_httpWriteResponseBody
    (JNIEnv *env, jclass, jlong _writer, jlong userData, jbyteArray _data)
{
    auto writer = (cq_http_body_writer)_writer;
    cqJNIByteArrayHelper data(env, _data);

    return (jboolean)writer((void *)userData, data.bytes(), data.length());
}
