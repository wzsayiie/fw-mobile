#pragma once

#include "cqcbasis.h"

typedef struct cq_window cq_window;

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

typedef struct cq_procedure {
    
    void (*load     )(cq_window *window);
    void (*appear   )(cq_window *window);
    void (*disappear)(cq_window *window);
    void (*unload   )(cq_window *window);
    
    void (*move   )(cq_window *window, float x, float y);
    void (*resize )(cq_window *window, float width, float height);
    void (*gl_draw)(cq_window *window);
    
    void (*update)(cq_window *window);
    
    void (*touch_began)(cq_window *window, float x, float y);
    void (*touch_moved)(cq_window *window, float x, float y);
    void (*touch_ended)(cq_window *window, float x, float y);
    
} cq_procedure;

CQ_C_LINK cq_window *cq_create_window(void);
CQ_C_LINK void cq_show_window(cq_window *window);

CQ_C_LINK void cq_set_procedure(cq_window *window, cq_procedure *procedure);

CQ_C_LINK void cq_set_window_extra(cq_window *window, int64_t extra);
CQ_C_LINK int64_t cq_window_extra(cq_window *window);

CQ_C_LINK bool cq_window_loaded (cq_window *window);
CQ_C_LINK bool cq_window_visible(cq_window *window);

CQ_C_LINK float cq_window_scale (cq_window *window);
CQ_C_LINK float cq_window_x     (cq_window *window);
CQ_C_LINK float cq_window_y     (cq_window *window);
CQ_C_LINK float cq_window_width (cq_window *window);
CQ_C_LINK float cq_window_height(cq_window *window);

//host need call these functions:
//
//NOTE: on android and ios, the functions must be called on the main thread.

typedef struct _cq_interfaces {
    
    int64_t (*create_window)(void);
    void    (*show_window  )(int64_t wid);
    
} _cq_interfaces;

CQ_C_LINK void _cq_install_interfaces(_cq_interfaces *interfaces);

CQ_C_LINK void _cq_notify_app_launch(void);

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

CQ_C_LINK void _cq_notify_window_load     (int64_t wid);
CQ_C_LINK void _cq_notify_window_appear   (int64_t wid);
CQ_C_LINK void _cq_notify_window_disappear(int64_t wid);
CQ_C_LINK void _cq_notify_window_unload   (int64_t wid);

CQ_C_LINK void _cq_notify_window_scale  (int64_t wid, float scale);
CQ_C_LINK void _cq_notify_window_origin (int64_t wid, float x, float y);
CQ_C_LINK void _cq_notify_window_size   (int64_t wid, float width, float height);
CQ_C_LINK void _cq_notify_window_gl_draw(int64_t wid);
CQ_C_LINK void _cq_notify_window_update (int64_t wid);

CQ_C_LINK void _cq_notify_window_touch_began(int64_t wid, float x, float y);
CQ_C_LINK void _cq_notify_window_touch_moved(int64_t wid, float x, float y);
CQ_C_LINK void _cq_notify_window_touch_ended(int64_t wid, float x, float y);

#ifdef __cplusplus

//use _cq_entry() to set program entry.

struct _cq_set_entry {
    _cq_set_entry(void (*entry)());
};

#define _cq_entry(ENTRY)\
/**/    static void ENTRY();\
/**/    static _cq_set_entry _cq_entry##ENTRY(ENTRY);\
/**/    void ENTRY()

#endif
