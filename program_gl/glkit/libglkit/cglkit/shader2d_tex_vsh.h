R"GLSL(

uniform   vec2 cq_ViewCenter;
attribute vec2 vecPosition;
attribute vec2 texPosition;
varying   vec2 texCoord;

void main() {
    float x = vecPosition.x - cq_ViewCenter.x;
    float y = vecPosition.y - cq_ViewCenter.y;
    gl_Position = vec4(x, y, 0.0, 1.0);

    texCoord = texPosition;
}

)GLSL"
