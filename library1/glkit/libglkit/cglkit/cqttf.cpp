#include "cqttf.h"
#include "cqdraw2d.h"

//ttf:

struct cq_ttf {
};

cq_ttf *cq_new_ttf(const char *path) {
    return (cq_ttf *)(1);
}

void cq_del_ttf(cq_ttf *ttf) {
}

//font:

struct cq_font {
    cq_ttf *ttf;
    float size;
};

cq_font *cq_new_font(cq_ttf *ttf, float size) {
    if (ttf == nullptr) {
        return nullptr;
    }
    if (size <= 0) {
        return nullptr;
    }
    
    cq_font *font = new cq_font;
    font->ttf = ttf;
    font->size = size;
    return font;
}

cq_ttf *cq_font_ttf(cq_font *font) {
    if (font != nullptr) {
        return font->ttf;
    }
    return nullptr;
}

float cq_font_size(struct cq_font *font) {
    if (font != nullptr) {
        return font->size;
    }
    return 0;
}

void cq_del_font(cq_font *font) {
    delete font;
}

//drawing string:

float cq_drawing_str_wide(cq_font *font, const char *str) {
    if (font == nullptr) {
        return 0;
    }
    if (cq_str_empty(str)) {
        return 0;
    }
    
    return font->size * strlen(str);
}

void cq_draw_str(float x, float y, cq_font *font, const char *str) {
    if (font == nullptr) {
        return;
    }
    if (cq_str_empty(str)) {
        return;
    }
    
    float s = font->size;
    size_t n = strlen(str);
    for (size_t i = 0; i < n; ++i) {
        cq_draw_path_start();
        cq_draw_path_add(x + 1    , y + 1    );
        cq_draw_path_add(x + s - 1, y + 1    );
        cq_draw_path_add(x + s - 1, y + s - 1);
        cq_draw_path_add(x + 1    , y + s - 1);
        cq_draw_path_stop();
        x += s;
    }
}
