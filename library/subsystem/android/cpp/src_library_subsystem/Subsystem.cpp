#include "cqsubsystemarche.h"
#include "cqjnihelper.hh"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/subsystem/Subsystem");
    }
    return clazz;
}

bool cq_subsystem_start(const char *name) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "cq_subsystem_start");
    method.push(name);
    return method.callBool();
}

void cq_subsystem_stop(const char *name) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "cq_subsystem_stop");
    method.push(name);
    method.callVoid();
}
