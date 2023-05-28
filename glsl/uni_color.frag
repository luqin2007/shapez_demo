#version 460 core

layout (location = 1) uniform vec4 fColor;

out vec4 color;

void main() {
    color = fColor;
}
