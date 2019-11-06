#pragma once

#include "cqcbasis.h"

//global configuration:

CQ_C_LINK float cq_wnd_scale(void);

//cq_wnd lifecycle:
//
// load --> appear <-> disappear --> unload
//  |         |            |           |
//  |update ->|-- update ->|           |
//  |draw   ->|-- draw   ->|           |
//  |         |-- touch  ->|           |
//  |         |            |           |
//  |move   ->|-- move   ->|- move   ->|
//  |resize ->|-- resize ->|- resize ->|

struct cq_wnd;

struct cq_wndproc {
    
    void (*load     )(struct cq_wnd *wnd);
    void (*appear   )(struct cq_wnd *wnd);
    void (*disappear)(struct cq_wnd *wnd);
    void (*unload   )(struct cq_wnd *wnd);
    
    void (*move  )(struct cq_wnd *wnd, float x, float y);
    void (*resize)(struct cq_wnd *wnd, float width, float height);
    void (*update)(struct cq_wnd *wnd);
    void (*gldraw)(struct cq_wnd *wnd);
    
    void (*pbegan)(struct cq_wnd *wnd, float x, float y);
    void (*pmoved)(struct cq_wnd *wnd, float x, float y);
    void (*pended)(struct cq_wnd *wnd, float x, float y);
};

CQ_C_LINK struct cq_wnd *cq_new_wnd(void);
CQ_C_LINK void cq_show_wnd(struct cq_wnd *wnd);

CQ_C_LINK void cq_set_wndproc(struct cq_wnd *wnd, struct cq_wndproc *proc);

CQ_C_LINK void cq_set_wnd_extra(struct cq_wnd *wnd, int64_t extra);
CQ_C_LINK int64_t cq_wnd_extra(struct cq_wnd *wnd);

CQ_C_LINK bool cq_wnd_loaded (struct cq_wnd *wnd);
CQ_C_LINK bool cq_wnd_visible(struct cq_wnd *wnd);

CQ_C_LINK float cq_wnd_x     (struct cq_wnd *wnd);
CQ_C_LINK float cq_wnd_y     (struct cq_wnd *wnd);
CQ_C_LINK float cq_wnd_width (struct cq_wnd *wnd);
CQ_C_LINK float cq_wnd_height(struct cq_wnd *wnd);

//host need call these functions:
//
//NOTE: on android and ios, the functions must be called on the main thread.

struct _cq_wndport {
    
    float   (*wnd_scale)(void);
    int64_t (*new_wnd  )(void);
    void    (*show_wnd )(int64_t wid);
};

CQ_C_LINK void _cq_init_wndport(struct _cq_wndport *port);

//wnd event notifications:
//
// |        load --> appear <-> disappear --> unload
// |         |         |            |           |
// |         |update ->|-- update ->|           |
// |         |draw   ->|-- draw   ->|           |
// |         |         |-- touch  ->|           |
// |         |         |            |           |
// |origin ->|origin ->|-- origin ->|- origin ->|
// |size   ->|size   ->|-- size   ->|- size   ->|

CQ_C_LINK void _cq_wnd_load     (int64_t wid);
CQ_C_LINK void _cq_wnd_appear   (int64_t wid);
CQ_C_LINK void _cq_wnd_disappear(int64_t wid);
CQ_C_LINK void _cq_wnd_unload   (int64_t wid);

CQ_C_LINK void _cq_wnd_origin(int64_t wid, float x, float y);
CQ_C_LINK void _cq_wnd_size  (int64_t wid, float width, float height);
CQ_C_LINK void _cq_wnd_update(int64_t wid);
CQ_C_LINK void _cq_wnd_gldraw(int64_t wid);

CQ_C_LINK void _cq_wnd_pbegan(int64_t wid, float x, float y);
CQ_C_LINK void _cq_wnd_pmoved(int64_t wid, float x, float y);
CQ_C_LINK void _cq_wnd_pended(int64_t wid, float x, float y);
