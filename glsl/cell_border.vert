#version 440 core

layout (location = 0) uniform vec2 windowSize;

layout (location = 0) in vec2 pos;

void main() {
    float x = pos.x / windowSize.x * 2 - 1;
    float y = pos.y / windowSize.y * 2 - 1;
    gl_Position = vec4(x, y, 0, 1);
}