#version 440 core

layout (location = 1) uniform sampler2D tex;

layout (location = 2) uniform float alpha;

in vec2 fUV;

out vec4 color;

void main() {
    vec4 tColor = texture(tex, fUV);
    color = vec4(tColor.xyz, tColor.w * alpha);
}