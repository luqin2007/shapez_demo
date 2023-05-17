#version 460 core

layout (location = 0) uniform vec2 windowSize;

layout (location = 0) in vec4 pos_uv;

out vec2 fUV;

void main() {
    float x = pos_uv.x / windowSize.x * 2 - 1;
    float y = 1 - pos_uv.y / windowSize.y * 2;
    gl_Position = vec4(x, y, 0, 1);
    fUV = vec2(pos_uv.zw);
}