R"GLSL(

uniform   vec2 cq_Offset;
attribute vec2 position;

void main() {
    float x = position.x + cq_Offset.x;
    float y = position.y + cq_Offset.y;
    gl_Position = vec4(x, y, 0.0, 1.0);
}

)GLSL"
