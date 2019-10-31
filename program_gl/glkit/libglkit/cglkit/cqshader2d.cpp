#include "cqshader2d_p.h"
#include "cqfoundation.hh"
#include "cqopengl_p.h"

static GLuint compile_shader(GLenum type, const char *source) {
    //compile.
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    //get log.
    char info[128] = "\0";
    GLint okay = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &okay);
    if (!okay) {
        glGetShaderInfoLog(shader, sizeof(info), NULL, info);
    }
    
    //return.
    if (!okay) {
        I("GLSL compile failed: %s", info);
        glDeleteShader(shader);
        return 0;
    } else {
        return shader;
    }
}

static GLuint build_program(const char *vsh_src, const char *fsh_src) {
    //compile.
    GLuint vsh = compile_shader(GL_VERTEX_SHADER, vsh_src);
    if (vsh == 0) {
        return 0;
    }
    
    GLuint fsh = compile_shader(GL_FRAGMENT_SHADER, fsh_src);
    if (fsh == 0) {
        glDeleteShader(vsh);
        return 0;
    }
    
    //link.
    GLuint program = glCreateProgram();
    glAttachShader(program, vsh);
    glAttachShader(program, fsh);
    glLinkProgram(program);
    
    glDeleteShader(vsh);
    glDeleteShader(fsh);
    
    //get log.
    char info[128] = "\0";
    GLint okay = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &okay);
    if (!okay) {
        glGetProgramInfoLog(program, sizeof(info), NULL, info);
    }
    
    //return.
    if (!okay) {
        glDeleteProgram(program);
        I("GLSL link failed: %s", info);
        return 0;
    } else {
        return program;
    }
}

//program:

static GLuint _active_program = 0;

static void use_program(GLuint program) {
    if (_active_program != program) {
        _active_program = program;
        glUseProgram(program);
    }
}

void cq_shader_use_graph_program(void) {
    static GLuint program = 0;
    static bool waiting = true;
    if (waiting) {
        const char *vsh =
        #include "shader2d_graph_vsh.h"
        ;
        const char *fsh =
        #include "shader2d_graph_fsh.h"
        ;
        program = build_program(vsh, fsh);
        waiting = false;
    }
    
    use_program(program);
}

void cq_shader_use_tex_program(void) {
    static GLuint program = 0;
    static bool waiting = true;
    if (waiting) {
        const char *vsh =
        #include "shader2d_tex_vsh.h"
        ;
        const char *fsh =
        #include "shader2d_tex_fsh.h"
        ;
        program = build_program(vsh, fsh);
        waiting = false;
    }
    
    use_program(program);
}

//get attribute variable:

int32_t cq_shader_attrib_loc(const char *name) {
    if (_active_program != 0 && !cq_str_empty(name)) {
        return glGetAttribLocation(_active_program, name);
    } else {
        return -1;
    }
}

//set uniform variable:

static int uniform_loc(const char *name) {
    if (_active_program != 0 && !cq_str_empty(name)) {
        return glGetUniformLocation(_active_program, name);
    } else {
        return -1;
    }
}

void cq_shader_set_1f(const char *name, float x) {
    int loc = uniform_loc(name);
    if (loc != -1) {
        glUniform1f(loc, x);
    }
}

void cq_shader_set_2f(const char *name, float x, float y) {
    int loc = uniform_loc(name);
    if (loc != -1) {
        glUniform2f(loc, x, y);
    }
}

void cq_shader_set_3f(const char *name, float x, float y, float z) {
    int loc = uniform_loc(name);
    if (loc != -1) {
        glUniform3f(loc, x, y, z);
    }
}

void cq_shader_set_4f(const char *name, float x, float y, float z, float w) {
    int loc = uniform_loc(name);
    if (loc != -1) {
        glUniform4f(loc, x, y, z, w);
    }
}
