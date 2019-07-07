#version 330

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec3 vNormal;

out vec3 fColor;
out vec3 fNormal;
out vec3 fPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * transform * vec4(inPos, 1.0);
//    gl_Position = transform*vec4(inPos, 1.0f);
    fPos = vec3(transform * vec4(inPos, 1.0));
    fColor = vColor;
    fNormal = vNormal;
}
