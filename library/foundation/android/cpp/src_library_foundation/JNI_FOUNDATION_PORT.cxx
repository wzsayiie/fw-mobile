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

uint8_t *cq_ios_bundle_res(int32_t *len, const char *, const char *) {
    if (len != nullptr) {
        *len = 0;
    }
    return nullptr;
}

uint8_t *cq_andr_asset(int32_t *len, const char *name) {
    static jmethodID methodID = nullptr;

    //1. get method.
    JNIEnv *env = cqJNIGetEnv();
    jclass cls = clazz();
    if (methodID == nullptr) {
        const char *signature = "(Ljava/lang/String;)[B";
        cqJNIGetStatic(&methodID, env, cls, "cq_andr_asset", signature);
    }
    if (methodID == nullptr) {
        return nullptr;
    }

    //2. call.
    jbyteArray jData = nullptr; {
        jstring jName = cqJNIStringFromU8(env, name);
        jData = (jbyteArray) env->CallStaticObjectMethod(cls, methodID, jName);
        env->DeleteLocalRef(jName);
    }
    if (jData == nullptr) {
        return nullptr;
    }

    //3. convert.
    jbyte *jBytes = env->GetByteArrayElements(jData, nullptr);
    int32_t jLen = env->GetArrayLength(jData);
    if (jBytes == nullptr || jLen <= 0) {
        env->DeleteLocalRef(jData);
        if (len != nullptr) {
            *len = 0;
        }
        return nullptr;
    }

    auto bytes = (uint8_t *)malloc((size_t)jLen);
    memcpy(bytes, jBytes, (size_t)jLen);
    env->ReleaseByteArrayElements(jData, jBytes, 0);
    env->DeleteLocalRef(jData);

    if (len != nullptr) {
        *len = (int32_t)jLen;
    }
    return bytes;
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

//thread:

void cq_thread_run(void (*task)(void *), void *data) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_thread_run");

    method.push((jlong)task);
    method.push((jlong)data);

    method.callVoid();
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_threadBody
    (JNIEnv *, jclass, jlong task, jlong data)
{
    auto taskFunc = (void (*)(void *))task;
    auto dataRef = (void *)data;
    taskFunc(dataRef);
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

    return cq_store_str(method.callString().c_str());
}

extern "C" JNIEXPORT jint JNICALL Java_src_library_foundation_PORT_httpReadRequestBody
    (JNIEnv *env, jclass, jlong reader, jlong userData, jbyteArray buffer)
{
    auto func = (cq_http_body_reader)reader;

    jsize len = env->GetArrayLength(buffer);
    std::vector<jbyte> data((size_t)len);

    int32_t readLen = func((void *)userData, data.data(), len);
    if (readLen > 0) {
        env->SetByteArrayRegion(buffer, 0, readLen, data.data());
    }
    return readLen;
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_httpWriteResponseCode
    (JNIEnv *, jclass, jlong writer, jlong userData, jint responseCode)
{
    auto func = (cq_http_code_writer)writer;
    func((void *)userData, (int32_t)responseCode);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_PORT_httpWriteResponseHeader
    (JNIEnv *env, jclass, jlong writer, jlong userData, jstring field, jstring value)
{
    auto func = (cq_http_header_writer)writer;
    std::string f = cqJNIU8StringFromJNI(env, field);
    std::string v = cqJNIU8StringFromJNI(env, value);

    func((void *)userData, f.c_str(), v.c_str());
}

extern "C" JNIEXPORT jboolean JNICALL Java_src_library_foundation_PORT_httpWriteResponseBody
    (JNIEnv *env, jclass, jlong writer, jlong userData, jbyteArray data)
{
    auto func = (cq_http_body_writer)writer;
    jbyte *bytes = env->GetByteArrayElements(data, nullptr);
    jsize length = env->GetArrayLength(data);

    auto ret = (jboolean)func((void *)userData, bytes, (int32_t)length);

    env->ReleaseByteArrayElements(data, bytes, JNI_ABORT);

    return ret;
}
