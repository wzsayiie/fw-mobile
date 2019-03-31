#pragma once

#include "cqconvention.h"

CQ_C_LINK void _main(void);

typedef struct cq_window cq_window;

typedef struct cq_window_procedure {
    
    void (*load)(cq_window *window);
    void (*show)(cq_window *window);
    void (*hide)(cq_window *window);
    
    void (*touch_began)(cq_window *window, float x, float y);
    void (*touch_moved)(cq_window *window, float x, float y);
    void (*touch_ended)(cq_window *window, float x, float y);
    
} cq_window_procedure;

CQ_C_LINK cq_window *cq_window_create(void);
CQ_C_LINK void cq_window_show(cq_window *window);

CQ_C_LINK void cq_window_set_background_color(cq_window *window, float r, float g, float b);
CQ_C_LINK void cq_window_set_procedure(cq_window *window, cq_window_procedure *procedure);
CQ_C_LINK cq_window_procedure *cq_window_get_procedure(cq_window *window);
