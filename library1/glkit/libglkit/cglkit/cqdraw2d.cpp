#include "cqdraw2d.h"
#include "cqcppbasis.hh"
#include "cqopengl_p.h"
#include "cqshader2d_p.h"
#include "cqwnd.h"

//configuration:

static int32_t _coord_mode = 0;

static float wld_scr_coord_x(float w, float x) {return (x / w * 2.f);}
static float wld_scr_coord_y(float h, float y) {return (y / h * 2.f);}
static float wld_tex_coord_x(float w, float x) {return (x / w * 2.f) - 1.f;}
static float wld_tex_coord_y(float h, float y) {return (y / h * 2.f) - 1.f;}

static float pic_scr_coord_x(float w, float x) {return   (x / w * 2.f) - 1.f;}
static float pic_scr_coord_y(float h, float y) {return - (y / h * 2.f) + 1.f;}
static float pic_tex_coord_x(float w, float x) {return   (x / w * 2.f) - 1.f;}
static float pic_tex_coord_y(float h, float y) {return - (y / h * 2.f) + 1.f;}

static float coord_x(bool scr, float w, float x) {
    switch (_coord_mode) {
        case cq_coord_mode_wld: return scr ? wld_scr_coord_x(w, x) : wld_tex_coord_x(w, x);
        case cq_coord_mode_pic: return scr ? pic_scr_coord_x(w, x) : pic_tex_coord_x(w, x);
        default: return 0;
    }
}

static float coord_y(bool scr, float h, float y) {
    switch (_coord_mode) {
        case cq_coord_mode_wld: return scr ? wld_scr_coord_y(h, y) : wld_tex_coord_y(h, y);
        case cq_coord_mode_pic: return scr ? pic_scr_coord_y(h, y) : pic_tex_coord_y(h, y);
        default: return 0;
    }
}

static float wld_scr_offset_x(float w, float x) {return (x / w * 2.f);}
static float wld_scr_offset_y(float h, float y) {return (y / h * 2.f);}
static float wld_tex_offset_x(float w, float x) {return (x / w * 2.f);}
static float wld_tex_offset_y(float h, float y) {return (y / h * 2.f);}

static float pic_scr_offset_x(float w, float x) {return   (x / w * 2.f);}
static float pic_scr_offset_y(float h, float y) {return - (y / h * 2.f);}
static float pic_tex_offset_x(float w, float x) {return   (x / w * 2.f);}
static float pic_tex_offset_y(float h, float y) {return - (y / h * 2.f);}

static float offset_x(bool scr, float w, float x) {
    switch (_coord_mode) {
        case cq_coord_mode_wld: return scr ? wld_scr_offset_x(w, x) : wld_tex_offset_x(w, x);
        case cq_coord_mode_pic: return scr ? pic_scr_offset_x(w, x) : pic_tex_offset_x(w, x);
        default: return 0;
    }
}

static float offset_y(bool scr, float h, float y) {
    switch (_coord_mode) {
        case cq_coord_mode_wld: return scr ? wld_scr_offset_y(h, y) : wld_tex_offset_y(h, y);
        case cq_coord_mode_pic: return scr ? pic_scr_offset_y(h, y) : pic_tex_offset_y(h, y);
        default: return 0;
    }
}

static void wld_tex_order(float *order) {
    order[0] = 0.f; order[1] = 0.f;
    order[2] = 1.f; order[3] = 0.f;
    order[4] = 1.f; order[5] = 1.f;
    order[6] = 0.f; order[7] = 1.f;
}

static void pic_tex_order(float *order) {
    order[0] = 0.f; order[1] = 1.f;
    order[2] = 1.f; order[3] = 1.f;
    order[4] = 1.f; order[5] = 0.f;
    order[6] = 0.f; order[7] = 0.f;
}

static void tex_order(float *order) {
    switch (_coord_mode) {
        case cq_coord_mode_wld: wld_tex_order(order); break;
        case cq_coord_mode_pic: pic_tex_order(order); break;
        default:;
    }
}

void cq_set_coord_mode(int32_t mode) {
    _coord_mode = mode;
}

static float _camera_x = 0;
static float _camera_y = 0;

void cq_set_camera_pos(float x, float y) {
    _camera_x = x;
    _camera_y = y;
}

void cq_enable_alpha(bool enabled) {
    if (enabled) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}

//texture:

struct cq_tex {
    GLuint  tex;
    int32_t pw;
    int32_t ph;
};

static cq_tex *cq_new_formatted_tex(int32_t pw, int32_t ph, GLint format, const void *data) {
    if (pw <= 0 || ph <= 0) {
        return nullptr;
    }
    
    cq_tex *tex = new cq_tex;
    tex->pw = pw;
    tex->ph = ph;
    
    glGenTextures(1, &tex->tex);
    glBindTexture(GL_TEXTURE_2D, tex->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, format, pw, ph, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return tex;
}

cq_tex *cq_new_tex(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_tex(pw, ph, GL_RGBA, data);
}

cq_tex *cq_new_rgb_tex(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_tex(pw, ph, GL_RGB, data);
}

int32_t cq_tex_pw(struct cq_tex *tex) {return tex ? tex->pw : 0;}
int32_t cq_tex_ph(struct cq_tex *tex) {return tex ? tex->ph : 0;}

void cq_del_tex(cq_tex *tex) {
    if (tex != nullptr) {
        glDeleteTextures(1, &tex->tex);
    }
}

//frame buffer object:

struct cq_fbo {
    GLuint  fbo;
    cq_tex *tex;
};

static cq_fbo *cq_new_formatted_fbo(int32_t pw, int32_t ph, GLint format, const void *data) {
    if (pw <= 0 || ph <= 0) {
        return nullptr;
    }
    
    cq_fbo *fbo = new cq_fbo;
    
    //new tex.
    fbo->tex = cq_new_formatted_tex(pw, ph, format, data);
    //new fbo.
    glGenFramebuffers(1, &fbo->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->tex->tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    return fbo;
}

cq_fbo *cq_new_fbo(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_fbo(pw, ph, GL_RGBA, data);
}

cq_fbo *cq_new_rgb_fbo(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_fbo(pw, ph, GL_RGB, data);
}

cq_tex *cq_fbo_tex(cq_fbo *fbo) {
    if (fbo != nullptr) {
        return fbo->tex;
    } else {
        return nullptr;
    }
}

void cq_del_fbo(cq_fbo *fbo) {
    if (fbo != nullptr) {
        glDeleteFramebuffers(1, &fbo->fbo);
        cq_del_tex(fbo->tex);
    }
}

//draw fbo:

extern cq_fbo *const CQ_SCREEN_FBO = (cq_fbo *)(-1);

static cq_fbo *_active_fbo = nullptr;
static bool _active_is_scr = true;
static float _active_fbo_w = 0;
static float _active_fbo_h = 0;

static float _color_r = 0;
static float _color_g = 0;
static float _color_b = 0;
static float _color_a = 0;

void cq_begin_draw_fbo(float w, float h, cq_fbo *fbo) {
    if (w <= 0 || h <= 0 || fbo == nullptr) {
        return;
    }
    
    if (_active_fbo != fbo) {
        if (fbo == CQ_SCREEN_FBO) {
            float scale = cq_wnd_scale();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, w * scale, h * scale);
        } else {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo);
            glViewport(0, 0, fbo->tex->pw, fbo->tex->ph);
        }
    }
    _active_fbo = fbo;
    _active_is_scr = (fbo == CQ_SCREEN_FBO);
    _active_fbo_w = w;
    _active_fbo_h = h;
}

void cq_end_draw_fbo() {
}

void cq_clear_current(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void cq_set_draw_color(float r, float g, float b, float a) {
    _color_r = r;
    _color_g = g;
    _color_b = b;
    _color_a = a;
}

//draw polygon on fbo:

static std::vector<float> _drawing_path;

static void add_drawing_point(float x, float y) {
    float a = coord_x(_active_is_scr, _active_fbo_w, x);
    float b = coord_y(_active_is_scr, _active_fbo_h, y);
    _drawing_path.push_back(a);
    _drawing_path.push_back(b);
}

static int32_t drawing_points_count() {
    return (int32_t)_drawing_path.size() / 2;
}

void cq_draw_path_start() {
    _drawing_path.clear();
}

void cq_draw_path_start_at(float x, float y) {
    cq_draw_path_start();
    add_drawing_point(x, y);
}

void cq_draw_path_add_at(float x, float y) {
    add_drawing_point(x, y);
}

void cq_draw_path_stop_at(float x, float y) {
    add_drawing_point(x, y);
    cq_draw_path_stop();
}

void cq_draw_path_stop() {
    if (_drawing_path.empty()) {
        return;
    }
    
    cq_shader_use_graph_program();
    
    //assign "cq_Offset".
    float off_x = 0;
    float off_y = 0;
    if (_active_is_scr) {
        off_x = offset_x(true, _active_fbo_w, -_camera_x);
        off_y = offset_y(true, _active_fbo_h, -_camera_y);
    }
    cq_shader_set_2f("cq_Offset", off_x, off_y);
    
    //assign "color".
    cq_shader_set_4f("color", _color_r, _color_g, _color_b, _color_a);
    
    //assign "position".
    int32_t position = cq_shader_attrib_loc("position");
    glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, _drawing_path.data());
    glEnableVertexAttribArray(position);
    
    //draw.
    glDrawArrays(GL_TRIANGLE_FAN, 0, drawing_points_count());
    
    _drawing_path.clear();
}

//draw texture on fbo:

void cq_draw_tex(float x, float y, float w, float h, cq_tex *tex) {
    if (w <= 0 || h <= 0 || tex == nullptr) {
        return;
    }
    
    cq_shader_use_tex_program();
    
    //assign "cq_Offset".
    float off_x = 0;
    float off_y = 0;
    if (_active_is_scr) {
        off_x = offset_x(true, _active_fbo_w, -_camera_x);
        off_y = offset_y(true, _active_fbo_h, -_camera_y);
    }
    cq_shader_set_2f("cq_Offset", off_x, off_y);
    
    //assign "texSimple".
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex->tex);
    
    //assign "vecPosition".
    float x_min = coord_x(_active_is_scr, _active_fbo_w, x);
    float x_max = coord_x(_active_is_scr, _active_fbo_w, x + w);
    float y_min = coord_y(_active_is_scr, _active_fbo_h, y);
    float y_max = coord_y(_active_is_scr, _active_fbo_h, y + h);
    float vecCoord[] = {
        x_min, y_min,
        x_max, y_min,
        x_max, y_max,
        x_min, y_max,
    };
    int32_t vecPosition = cq_shader_attrib_loc("vecPosition");
    glVertexAttribPointer(vecPosition, 2, GL_FLOAT, GL_FALSE, 0, vecCoord);
    glEnableVertexAttribArray(vecPosition);
    
    //assign "texPosition".
    float texCoord[8] = {0};
    tex_order(texCoord);
    
    int32_t texPosition = cq_shader_attrib_loc("texPosition");
    glVertexAttribPointer(texPosition, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
    glEnableVertexAttribArray(texPosition);
    
    //draw.
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}
