#include "cqfoundationarche.h"
#include "cqjnihelper.hh"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/foundation/Foundation");
    }
    return clazz;
}

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
