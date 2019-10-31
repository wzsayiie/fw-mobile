#pragma once

#include "cqcbasis.h"

//program:
CQ_C_LINK void cq_shader_use_graph_program(void);
CQ_C_LINK void cq_shader_use_tex_program(void);

//get attribute variable:
CQ_C_LINK int32_t cq_shader_attrib_loc(const char *name);

//set uniform variable:
CQ_C_LINK void cq_shader_set_1f(const char *name, float x);
CQ_C_LINK void cq_shader_set_2f(const char *name, float x, float y);
CQ_C_LINK void cq_shader_set_3f(const char *name, float x, float y, float z);
CQ_C_LINK void cq_shader_set_4f(const char *name, float x, float y, float z, float w);
