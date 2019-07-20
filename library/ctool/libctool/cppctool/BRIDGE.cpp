#include "cqctoolarche.h"
#include "cqctool.hh"

bool cq_main_queue_empty() {
    return cqDispatch::mainQueueEmpty();
}

void cq_update_main_queue() {
    cqDispatch::updateMain();
}
