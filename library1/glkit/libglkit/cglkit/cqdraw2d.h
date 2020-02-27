#pragma once

#include "cqcbasis.h"

//configuration:

//screen:        texture:
// +---------+    +------+
// |    ↑y   |    ↑y     |
// |    |    |    |      |
// | ---+--->|    |      |
// |    |   x|    |      |
// |    |    |    +----->+
// +---------+          x
//
static const int32_t cq_coord_mode_wld = 1;

//screen:    texture:
// +---->+    +---->+
// |    x|    |    x|
// |     |    |     |
// ↓y    |    ↓y    |
// +-----+    +-----+
//
static const int32_t cq_coord_mode_pic = 2;

CQ_C_LINK void cq_set_coord_mode(int32_t mode);
CQ_C_LINK void cq_set_camera_pos(float x, float y);
CQ_C_LINK void cq_enable_alpha(bool enabled);

//texture:

cq_struct(cq_tex);

//parameters [pw, ph] is pixel size.
CQ_C_LINK cq_tex *cq_new_tex    (int32_t pw, int32_t ph, const void *data);
CQ_C_LINK cq_tex *cq_new_rgb_tex(int32_t pw, int32_t ph, const void *data);

CQ_C_LINK int32_t cq_tex_pw(cq_tex *tex);
CQ_C_LINK int32_t cq_tex_ph(cq_tex *tex);

CQ_C_LINK void cq_del_tex(cq_tex *tex);

//frame buffer object:

cq_struct(cq_fbo);

CQ_C_LINK cq_fbo *cq_new_fbo    (int32_t pw, int32_t ph, const void *data);
CQ_C_LINK cq_fbo *cq_new_rgb_fbo(int32_t pw, int32_t ph, const void *data);

CQ_C_LINK cq_tex *cq_fbo_tex(cq_fbo *fbo);

CQ_C_LINK void cq_del_fbo(cq_fbo *fbo);

//draw fbo:

//default screen frame buffer.
extern cq_fbo *const CQ_SCREEN_FBO;

CQ_C_LINK void cq_begin_draw_fbo(float w, float h, cq_fbo *fbo);
CQ_C_LINK void cq_end_draw_fbo(void);

CQ_C_LINK void cq_clear_current(float r, float g, float b, float a);

CQ_C_LINK void cq_set_draw_color(float r, float g, float b, float a);

//draw polygon on fbo:
CQ_C_LINK void cq_draw_path_start(void);
CQ_C_LINK void cq_draw_path_add(float x, float y);
CQ_C_LINK void cq_draw_path_stop(void);

//draw texture on fbo:
CQ_C_LINK void cq_draw_tex(float x, float y, float w, float h, cq_tex *tex);
