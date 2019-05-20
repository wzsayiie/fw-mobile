#pragma once

#include "cqcbasis.h"

typedef struct cq_window cq_window;

typedef struct cq_window_procedure {
    
    void (*load)(cq_window *window);
    void (*show)(cq_window *window);
    void (*hide)(cq_window *window);
    
    void (*touch_began)(cq_window *window, float x, float y);
    void (*touch_moved)(cq_window *window, float x, float y);
    void (*touch_ended)(cq_window *window, float x, float y);
    
} cq_window_procedure;

CQ_C_LINK cq_window *cq_window_get_default(void);

CQ_C_LINK void                 cq_window_set_procedure(cq_window *w, cq_window_procedure *p);
CQ_C_LINK cq_window_procedure *cq_window_get_procedure(cq_window *w);

CQ_C_LINK void    cq_window_set_extra(cq_window *window, int64_t extra);
CQ_C_LINK int64_t cq_window_get_extra(cq_window *window);

CQ_C_LINK float cq_window_get_width       (cq_window *window);
CQ_C_LINK float cq_window_get_height      (cq_window *window);
CQ_C_LINK float cq_window_get_screen_scale(cq_window *window);

//host need call these functions ->

CQ_C_LINK void _cq_install_window_get_width_handler       (float (*h)(int64_t));
CQ_C_LINK void _cq_install_window_get_height_handler      (float (*h)(int64_t));
CQ_C_LINK void _cq_install_window_get_screen_scale_handler(float (*h)(int64_t));

CQ_C_LINK void _cq_notify_default_window_created(int64_t window_idx);
CQ_C_LINK void _cq_notify_window_load(int64_t window_idx);
CQ_C_LINK void _cq_notify_window_show(int64_t window_idx);
CQ_C_LINK void _cq_notify_window_hide(int64_t window_idx);
CQ_C_LINK void _cq_notify_window_touch_began(int64_t window_idx, float x, float y);
CQ_C_LINK void _cq_notify_window_touch_moved(int64_t window_idx, float x, float y);
CQ_C_LINK void _cq_notify_window_touch_ended(int64_t window_idx, float x, float y);

//user need implement this function ->

CQ_C_LINK void _cq_default_window_created(void);
