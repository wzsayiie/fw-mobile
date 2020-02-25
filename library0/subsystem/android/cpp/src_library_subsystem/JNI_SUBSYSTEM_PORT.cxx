#include "cqsubsystemarche.h"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(PORT, "src/library/subsystem/PORT");

void cq_subsystem_start() {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_subsystem_start");
    method.fn<void>();
}

void cq_subsystem_stop() {
    CQ_JNI_STATIC_METHOD(PORT, method, "cq_subsystem_stop");
    method.fn<void>();
}
