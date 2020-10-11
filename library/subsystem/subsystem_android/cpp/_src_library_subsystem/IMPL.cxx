#include "cqsubsystemintf.h"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(PORT, "src/library/subsystem/IMPL");

void cq_subsystem_start() {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>();
}

void cq_subsystem_stop() {
    CQ_JNI_STATIC_METHOD(PORT, method, __func__);
    method.fn<void>();
}
