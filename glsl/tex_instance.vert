#version 440 core

layout (location = 0) uniform vec2 windowSize;

layout (location = 0) in vec4 p0;
layout (location = 1) in vec4 p1;
layout (location = 2) in int idx;

out vec2 fUV;

void main() {
    vec2 xy;
    switch (idx) {
        case 0:
            xy = vec2(p0.x, p0.y);
            fUV = vec2(p0.z, p0.w);
            break;
        case 1:
            xy = vec2(p0.x, p1.y);
            fUV = vec2(p0.z, p1.w);
            break;
        case 2:
            xy = vec2(p1.x, p1.y);
            fUV = vec2(p1.z, p1.w);
            break;
        case 3:
            xy = vec2(p1.x, p0.y);
            fUV = vec2(p1.z, p0.w);
            break;
        default: 
            xy = vec2(0, 0);
            fUV = vec2(0, 0);
    }
    
    float x = xy.x / windowSize.x * 2 - 1;
    float y = 1 - xy.y / windowSize.y * 2;
    gl_Position = vec4(x, y, 0, 1);
}