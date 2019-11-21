#include "cqttf.h"

struct cq_ttf {
};

cq_ttf *cq_new_ttf(const char *path) {
    return nullptr;
}

void cq_del_ttf(cq_ttf *ttf) {
}

struct cq_font {
};

cq_font *cq_new_font(cq_ttf *ttf, float size) {
    return nullptr;
}

void cq_del_font(cq_font *font) {
}

float cq_drawing_str_len(cq_font *font, const char *str) {
    return 0;
}

void cq_draw_str(float x, float y, cq_font *font, const char *str) {
}
