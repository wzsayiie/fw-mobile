#include "cqgraphics.hh"
#include "cqopengl.h"
#include "cqwindow.hh"

static cqWindowRef sWindow;

static GLuint sGLProgram = 0;
static int sGLVarPosition = 0;
static int sGLVarColor = 0;

static cqColor sSelectedColor;

cqContext::cqContext(float x, float y): offsetX(x), offsetY(y) {
}

void cqContext::setFillColor(cqColor color) {
    sSelectedColor = color;
}

void cqContext::fillRect(cqRect rect) {
    
    //color:
    cqColor color = sSelectedColor;
    glUniform4f(sGLVarColor, color.red, color.green, color.blue, color.alpha);
    
    //position:
    float w = sWindow->frame().size.width;
    float h = sWindow->frame().size.height;
    
    GLfloat lft = -1.f + (offsetX + rect.minX()) / w * 2.f;
    GLfloat rht = -1.f + (offsetX + rect.maxX()) / w * 2.f;
    GLfloat top =  1.f - (offsetY + rect.minY()) / h * 2.f;
    GLfloat bot =  1.f - (offsetY + rect.maxY()) / h * 2.f;
    
    GLfloat vertices[] = {
        lft, top, 0.f,
        rht, top, 0.f,
        lft, bot, 0.f,
        rht, bot, 0.f,
    };
    glVertexAttribPointer(sGLVarPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(sGLVarPosition);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

static GLuint compileShader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    return shader;
}

void cqGraphics::startupGraphicsProgram(cqWindowRef window) {
    
    sWindow = window;
    
    //set alpha channel available.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    
    //compile shaders.
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER,
        "attribute vec3 position;"
        "void main() {"
        "    gl_Position = vec4(position, 1.0);"
        "}"
    );
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,
        "precision mediump float;"
        "uniform vec4 color;"
        "void main() {"
        "    gl_FragColor = color;"
        "}"
    );
    
    //link
    sGLProgram = glCreateProgram();
    
    glAttachShader(sGLProgram, vertexShader);
    glAttachShader(sGLProgram, fragmentShader);
    glLinkProgram(sGLProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glUseProgram(sGLProgram);
    
    //gl parematers
    sGLVarPosition = glGetAttribLocation(sGLProgram, "position");
    sGLVarColor = glGetUniformLocation(sGLProgram, "color");
}

void cqGraphics::prepareDraw() {
    //white background.
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static std::vector<cqContext> sStackedContexts;

void cqGraphics::pushContext(cqContext context) {
    sStackedContexts.push_back(context);
}

cqContext cqGraphics::currentContext() {
    if (sStackedContexts.empty()) {
        return cqContext(0, 0);
    } else {
        return sStackedContexts.back();
    }
}

void cqGraphics::popContext() {
    if (!sStackedContexts.empty()) {
        sStackedContexts.pop_back();
    }
}
