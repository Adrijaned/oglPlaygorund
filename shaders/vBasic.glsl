#version 330

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 vColor;

out vec3 fColor;

void main() {
    gl_Position = vec4(inPos, 1.0);
    fColor = vColor;
}
