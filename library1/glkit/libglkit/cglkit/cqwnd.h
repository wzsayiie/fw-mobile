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

cq_struct(cq_wnd);

cq_struct(cq_wndproc) {
    
    void (*load     )(cq_wnd *wnd);
    void (*appear   )(cq_wnd *wnd);
    void (*disappear)(cq_wnd *wnd);
    void (*unload   )(cq_wnd *wnd);
    
    void (*move  )(cq_wnd *wnd, float x, float y);
    void (*resize)(cq_wnd *wnd, float width, float height);
    void (*update)(cq_wnd *wnd);
    void (*gldraw)(cq_wnd *wnd);
    
    void (*pbegan)(cq_wnd *wnd, float x, float y);
    void (*pmoved)(cq_wnd *wnd, float x, float y);
    void (*pended)(cq_wnd *wnd, float x, float y);
};

CQ_C_LINK cq_wnd *cq_new_wnd(void);
CQ_C_LINK void cq_show_wnd(cq_wnd *wnd);

CQ_C_LINK void cq_set_wndproc(cq_wnd *wnd, cq_wndproc *proc);

CQ_C_LINK void cq_set_wnd_extra(cq_wnd *wnd, int64_t extra);
CQ_C_LINK int64_t cq_wnd_extra(cq_wnd *wnd);

CQ_C_LINK bool cq_wnd_loaded (cq_wnd *wnd);
CQ_C_LINK bool cq_wnd_visible(cq_wnd *wnd);

CQ_C_LINK float cq_wnd_x     (cq_wnd *wnd);
CQ_C_LINK float cq_wnd_y     (cq_wnd *wnd);
CQ_C_LINK float cq_wnd_width (cq_wnd *wnd);
CQ_C_LINK float cq_wnd_height(cq_wnd *wnd);

//host need call these functions:
//
//NOTE: on android and ios, the functions must be called on the main thread.

cq_struct(_cq_wndport) {
    
    float   (*wnd_scale)(void);
    int64_t (*new_wnd  )(void);
    void    (*show_wnd )(int64_t wid);
};

CQ_C_LINK void _cq_init_wndport(_cq_wndport *port);

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
