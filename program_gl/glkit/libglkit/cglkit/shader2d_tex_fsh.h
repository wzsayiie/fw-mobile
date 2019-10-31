R"GLSL(

precision mediump float;

uniform sampler2D texSimple;
varying vec2 texCoord;

void main() {
    gl_FragColor = texture2D(texSimple, texCoord);
}

)GLSL"
