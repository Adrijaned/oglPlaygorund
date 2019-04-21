#version 330

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 vColor;

out vec3 fColor;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection *view* transform * vec4(inPos, 1.0);
//    gl_Position = transform*vec4(inPos, 1.0f);
    fColor = vColor;
}
