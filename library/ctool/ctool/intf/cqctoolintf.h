#pragma once

#include "cqcbasis.h"

CQ_C_LINK void cq_main_queue_user_control(bool enabled);
CQ_C_LINK bool cq_main_queue_empty(void);
CQ_C_LINK void cq_update_main_queue(void);
