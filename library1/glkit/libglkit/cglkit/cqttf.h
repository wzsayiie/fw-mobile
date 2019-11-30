#pragma once

#include "cqcbasis.h"

//ttf:

CQ_C_LINK struct cq_ttf *cq_new_ttf(const char *path);
CQ_C_LINK void cq_del_ttf(struct cq_ttf *ttf);

//font:

CQ_C_LINK struct cq_font *cq_new_font(struct cq_ttf *ttf, float size);

CQ_C_LINK struct cq_ttf *cq_font_ttf(struct cq_font *font);
CQ_C_LINK float cq_font_size(struct cq_font *font);

CQ_C_LINK void cq_del_font(struct cq_font *font);

//drawing string:

CQ_C_LINK float cq_drawing_str_wide(struct cq_font *font, const char *str);
CQ_C_LINK void cq_draw_str(float x, float y, struct cq_font *font, const char *str);
