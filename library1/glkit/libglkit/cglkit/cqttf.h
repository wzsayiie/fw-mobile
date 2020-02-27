#pragma once

#include "cqcbasis.h"

//ttf:

cq_struct(cq_ttf);

CQ_C_LINK cq_ttf *cq_new_ttf(const char *path);
CQ_C_LINK void cq_del_ttf(cq_ttf *ttf);

//font:

cq_struct(cq_font);

CQ_C_LINK cq_font *cq_new_font(cq_ttf *ttf, float size);

CQ_C_LINK cq_ttf *cq_font_ttf(cq_font *font);
CQ_C_LINK float cq_font_size(cq_font *font);

CQ_C_LINK void cq_del_font(cq_font *font);

//drawing string:

CQ_C_LINK float cq_drawing_str_wide(cq_font *font, const char *str);
CQ_C_LINK void cq_draw_str(float x, float y, cq_font *font, const char *str);
