#version 460 core

layout (location = 0) uniform vec4 color;
layout (location = 1) uniform sampler2D tex;

in vec2 fUV;

out vec4 fOut;

void main() {
    fOut = vec4(color.xyz, color.a * texture(tex, fUV).r);
}