#include "cqfoundationarche.h"
#include "cqjnihelper.hh"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/foundation/Foundation");
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

//file manager:

const char *cq_document_directory() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_document_directory");

    std::string ret = method.callString();
    return cq_store_string(ret.data());
}

const char *cq_caches_directory() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_caches_directory");

    std::string ret = method.callString();
    return cq_store_string(ret.data());
}

const char *cq_temporary_directory() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_temporary_directory");

    std::string ret = method.callString();
    return cq_store_string(ret.data());
}

const char *cq_append_path(const char *parent, const char *child) {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_append_path");

    method.push(parent);
    method.push(child);

    std::string ret = method.callString();
    return cq_store_string(ret.data());
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

extern "C" JNIEXPORT void JNICALL Java_src_library_foundation_Foundation_threadBody
/**/(JNIEnv *, jobject, jlong task, jlong data)
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

//net:

int32_t cq_http_get(const char *url, float timeout) {
    return 0;
}

void *cq_http_get_bytes() {
    return nullptr;
}

int32_t cq_http_get_size() {
    return 0;
}
