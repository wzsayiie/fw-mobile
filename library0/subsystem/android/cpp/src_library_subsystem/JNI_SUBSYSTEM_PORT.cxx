#include "cqsubsystemarche.h"
#include "cqjnihelper.hh"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIEnv::findClass(&clazz, cqJNIEnv::env(), "src/library/subsystem/PORT");
    }
    return clazz;
}

void cq_subsystem_start() {
    static jmethodID methodID = nullptr;
    cqJNIStatic method(clazz(), &methodID, "cq_subsystem_start");
    method.callVoid();
}

void cq_subsystem_stop() {
    static jmethodID methodID = nullptr;
    cqJNIStatic method(clazz(), &methodID, "cq_subsystem_stop");
    method.callVoid();
}
