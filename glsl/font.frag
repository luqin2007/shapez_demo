#version 460 core

layout (location = 1) uniform vec4 color;
layout (location = 2) uniform sampler2D tex;

in vec2 fUV;

out vec4 fOut;

void main() {
    fOut = vec4(color.rgb, color.a * texture(tex, fUV).r);
}