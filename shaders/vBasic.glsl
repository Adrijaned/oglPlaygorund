#version 330

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 vColor;

out vec3 fColor;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(inPos, 1.0);
    fColor = vColor;
}
