#include "cqctoolintf.h"
#include "cqctool.hh"

void cq_main_queue_user_control(bool enabled) {
    cqDispatch::setUserControlEnabled(enabled);
}

bool cq_main_queue_empty() {
    return cqDispatch::mainQueueEmpty();
}

void cq_update_main_queue() {
    cqDispatch::updateMain();
}
