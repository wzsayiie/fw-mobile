R"GLSL(

uniform   vec2 cq_ViewCenter;
attribute vec2 position;

void main() {
    float x = position.x - cq_ViewCenter.x;
    float y = position.y - cq_ViewCenter.y;
    gl_Position = vec4(x, y, 0.0, 1.0);
}

)GLSL"
