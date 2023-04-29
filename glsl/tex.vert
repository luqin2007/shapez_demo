#version 440 core

layout (location = 0) uniform vec2 windowSize;

layout (location = 0) in vec4 posAndTex;

out vec2 fUV;

void main() {
    fUV = posAndTex.zw;
    float x = posAndTex.x / windowSize.x * 2 - 1;
    float y = posAndTex.y / windowSize.y * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);
}