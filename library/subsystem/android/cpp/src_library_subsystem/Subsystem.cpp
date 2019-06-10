#include "cqsubsystemarche.h"
#include "cqjnihelper.hh"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/subsystem/Subsystem");
    }
    return clazz;
}

void cq_subsystem_start() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_subsystem_start");
    method.callVoid();
}

void cq_subsystem_stop() {
    static jmethodID methodID = nullptr;
    cqJNIStaticMethod method(clazz(), &methodID, "cq_subsystem_stop");
    method.callVoid();
}
