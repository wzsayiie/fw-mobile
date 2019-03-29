#pragma once

#include "cqconvention.h"

CQ_C_LINK void _main(void);

typedef struct cq_window {
    int64_t handle;
} cq_window;

typedef void (*cq_procedure)(cq_window window, int32_t message, int64_t arg1, int64_t arg2);

CQ_C_LINK cq_window cq_create_window(void);
CQ_C_LINK void cq_set_procedure(cq_window window, cq_procedure procedure);
CQ_C_LINK void cq_show_window(cq_window window);

CQ_C_LINK void cq_send_message(cq_window window, int32_t message, int64_t arg1, int64_t arg2);
