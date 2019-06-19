#pragma once

#include "cqcbasis.h"

struct cq_window;

//cq_window lifecycle:
//
// load --> appear <-> disappear --> unload
//  |         |            |           |
//  |draw   ->|-- draw   ->|           |
//  |update ->|-- update ->|           |
//  |         |-- touch  ->|           |
//  |         |            |           |
//  |move   ->|-- move   ->|- move   ->|
//  |resize ->|-- resize ->|- resize ->|

struct cq_procedure {
    
    void (*load     )(struct cq_window *window);
    void (*appear   )(struct cq_window *window);
    void (*disappear)(struct cq_window *window);
    void (*unload   )(struct cq_window *window);
    
    void (*move   )(struct cq_window *window, float x, float y);
    void (*resize )(struct cq_window *window, float width, float height);
    void (*glpaint)(struct cq_window *window);
    
    void (*update)(struct cq_window *window);
    
    void (*pbegan)(struct cq_window *window, float x, float y);
    void (*pmoved)(struct cq_window *window, float x, float y);
    void (*pended)(struct cq_window *window, float x, float y);
};

CQ_C_LINK struct cq_window *cq_create_window(void);
CQ_C_LINK void cq_show_window(struct cq_window *window);

CQ_C_LINK void cq_set_procedure(struct cq_window *window, struct cq_procedure *procedure);

CQ_C_LINK void cq_set_window_extra(struct cq_window *window, int64_t extra);
CQ_C_LINK int64_t cq_window_extra(struct cq_window *window);

CQ_C_LINK bool cq_window_loaded (struct cq_window *window);
CQ_C_LINK bool cq_window_visible(struct cq_window *window);

CQ_C_LINK float cq_window_scale (struct cq_window *window);
CQ_C_LINK float cq_window_x     (struct cq_window *window);
CQ_C_LINK float cq_window_y     (struct cq_window *window);
CQ_C_LINK float cq_window_width (struct cq_window *window);
CQ_C_LINK float cq_window_height(struct cq_window *window);

//host need call these functions:
//
//NOTE: on android and ios, the functions must be called on the main thread.

struct _cq_interfaces {
    
    int64_t (*create_window)(void);
    void    (*show_window  )(int64_t wid);
    
};

CQ_C_LINK void _cq_init_interfaces(struct _cq_interfaces *interfaces);

//window event notifications:
//
// |        load --> appear <-> disappear --> unload
// |         |         |            |           |
// |scale  ->|         |            |           |
// |         |draw   ->|-- draw   ->|           |
// |         |update ->|-- update ->|           |
// |         |         |-- touch  ->|           |
// |         |         |            |           |
// |origin ->|origin ->|-- origin ->|- origin ->|
// |size   ->|size   ->|-- size   ->|- size   ->|

CQ_C_LINK void _cq_window_load     (int64_t wid);
CQ_C_LINK void _cq_window_appear   (int64_t wid);
CQ_C_LINK void _cq_window_disappear(int64_t wid);
CQ_C_LINK void _cq_window_unload   (int64_t wid);

CQ_C_LINK void _cq_window_scale  (int64_t wid, float scale);
CQ_C_LINK void _cq_window_origin (int64_t wid, float x, float y);
CQ_C_LINK void _cq_window_size   (int64_t wid, float width, float height);
CQ_C_LINK void _cq_window_glpaint(int64_t wid);
CQ_C_LINK void _cq_window_update (int64_t wid);

CQ_C_LINK void _cq_window_pbegan(int64_t wid, float x, float y);
CQ_C_LINK void _cq_window_pmoved(int64_t wid, float x, float y);
CQ_C_LINK void _cq_window_pended(int64_t wid, float x, float y);
