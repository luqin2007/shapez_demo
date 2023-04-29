#version 440 core

layout (location = 1) uniform sampler2D tex;

in vec2 fUV;

out vec4 color;

void main() {
    color = texture(tex, fUV);
}