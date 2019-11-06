#include "cqdraw2d.h"
#include "cqcppbasis.hh"
#include "cqopengl_p.h"
#include "cqshader2d_p.h"

//global:

float cq_gl_x_from_ui(float w, float x) {
    return -1.f + (x / w * 2.f);
}

float cq_gl_y_from_ui(float h, float y) {
    return 1.f - (y / h * 2.f);
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

static uint32_t cq_new_formatted_tex(int32_t pw, int32_t ph, GLint format, const void *data) {
    GLuint tex = 0;
    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, format, pw, ph, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return tex;
}

uint32_t cq_new_tex(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_tex(pw, ph, GL_RGBA, data);
}

uint32_t cq_new_rgb_tex(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_tex(pw, ph, GL_RGB, data);
}

void cq_del_tex(uint32_t tex) {
    if (tex != 0) {
        glDeleteTextures(1, &tex);
    }
}

//frame buffer object:

extern const cq_fbo CQ_FBO_ZERO = {0, 0};

static cq_fbo cq_new_formatted_fbo(int32_t pw, int32_t ph, GLint format, const void *data) {
    
    GLuint tex = cq_new_formatted_tex(pw, ph, format, data);
    
    GLuint fbo = 0;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    cq_fbo ret = {0};
    ret.fbo = fbo;
    ret.tex = tex;
    return ret;
}

cq_fbo cq_new_fbo(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_fbo(pw, ph, GL_RGBA, data);
}

cq_fbo cq_new_rgb_fbo(int32_t pw, int32_t ph, const void *data) {
    return cq_new_formatted_fbo(pw, ph, GL_RGB, data);
}

void cq_del_fbo(cq_fbo fbo) {
    if (fbo.fbo != 0) {
        glDeleteFramebuffers(1, &fbo.fbo);
    }
    cq_del_tex(fbo.tex);
}

//draw fbo:

extern const cq_fbo CQ_SCREEN_FBO = {0};

static cq_fbo  _active_fbo    = {0};
static int32_t _active_fbo_pw = 0;
static int32_t _active_fbo_ph = 0;

static float _color_r = 0;
static float _color_g = 0;
static float _color_b = 0;
static float _color_a = 0;

void cq_begin_draw_fbo(int32_t pw, int32_t ph, cq_fbo fbo) {
    _active_fbo_pw = pw;
    _active_fbo_ph = ph;
    
    if (_active_fbo.fbo != fbo.fbo) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo.fbo);
        glViewport(0, 0, pw, ph);
    }
    _active_fbo = fbo;
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
    _drawing_path.push_back(cq_gl_x_from_ui(_active_fbo_pw , x));
    _drawing_path.push_back(cq_gl_y_from_ui(_active_fbo_ph, y));
}

static int32_t drawing_points_count() {
    return (int32_t)_drawing_path.size() / 2;
}

void cq_draw_path_start(float x, float y) {
    _drawing_path.clear();
    add_drawing_point(x, y);
}

void cq_draw_path_add(float x, float y) {
    add_drawing_point(x, y);
}

void cq_draw_path_stop(float x, float y) {
    add_drawing_point(x, y);
    
    cq_shader_use_graph_program();
    
    //assign "cq_ViewCenter".
    cq_shader_set_2f("cq_ViewCenter", 0, 0);
    
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

void cq_draw_tex(float x, float y, float w, float h, uint32_t tex) {
    cq_shader_use_tex_program();
    
    //assign "cq_ViewCenter".
    cq_shader_set_2f("cq_ViewCenter", 0, 0);
    
    //assign "texSimple".
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    //assign "vecPosition".
    float left  = cq_gl_x_from_ui(_active_fbo_pw, x);
    float right = cq_gl_x_from_ui(_active_fbo_pw, x + w);
    float top   = cq_gl_y_from_ui(_active_fbo_ph, y);
    float bott  = cq_gl_y_from_ui(_active_fbo_ph, y + h);
    float vecCoord[] = {
        left , top ,
        right, top ,
        right, bott,
        left , bott,
    };
    int32_t vecPosition = cq_shader_attrib_loc("vecPosition");
    glVertexAttribPointer(vecPosition, 2, GL_FLOAT, GL_FALSE, 0, vecCoord);
    glEnableVertexAttribArray(vecPosition);
    
    //assign "texPosition".
    float texCoord[] = {
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,
    };
    int32_t texPosition = cq_shader_attrib_loc("texPosition");
    glVertexAttribPointer(texPosition, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
    glEnableVertexAttribArray(texPosition);
    
    //draw.
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}
