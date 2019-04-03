#pragma once

#include "cqconvention.h"

CQ_C_LINK void _entry(void);

typedef struct cq_window_procedure cq_window_procedure;
typedef struct cq_window cq_window;

struct cq_window_procedure {
    
    void (*load)(cq_window *window);
    void (*show)(cq_window *window);
    void (*hide)(cq_window *window);
    
    void (*touch_began)(cq_window *window, float x, float y);
    void (*touch_moved)(cq_window *window, float x, float y);
    void (*touch_ended)(cq_window *window, float x, float y);
};

struct cq_window {
    cq_window_procedure procedure;
    int64_t host_data;
    int64_t user_data;
};

CQ_C_LINK cq_window *cq_window_create(void);
CQ_C_LINK void cq_window_load(cq_window *window);

CQ_C_LINK void cq_window_set_back_color(cq_window *window, float r, float g, float b);

CQ_C_LINK float cq_window_get_width(cq_window *window);
CQ_C_LINK float cq_window_get_height(cq_window *window);
CQ_C_LINK float cq_window_get_screen_scale(cq_window *window);
