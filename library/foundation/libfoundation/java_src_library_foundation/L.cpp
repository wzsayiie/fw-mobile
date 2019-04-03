#include "cqproto_log.h"
#include "cqjnihelper.hh"

static jclass GetClass() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/foundation/L");
    }
    return clazz;
}

void cq_log_info(const char *file, int32_t line, const char *message) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method;
    method.select(GetClass());
    method.select(&methodID, "info");

    method.push(file);
    method.push(line);
    method.push(message);

    method.callVoid();
}

void cq_log_error(const char *file, int32_t line, const char *message) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method;
    method.select(GetClass());
    method.select(&methodID, "error");

    method.push(file);
    method.push(line);
    method.push(message);

    method.callVoid();
}
