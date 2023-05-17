#version 460 core

layout (location = 0) in vec4 pos_uv;

out vec2 fUV;

void main() {
    gl_Position = vec4(pos_uv.xy, 0, 1);
    fUV = pos_uv.zw;
}