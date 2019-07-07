#version 330

in vec3 fColor;
in vec3 fNormal;
in vec3 fPos;

out vec4 FragColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;
const float AMBIENT_MULTIPLIER = 0.11;

void main() {
    vec3 lightDirection = normalize(lightPosition - fPos);
    float diffusionScale = min(max(dot(fNormal, lightDirection), 0.0f), 1.0f);
    vec3 lightColorMultiplier = lightColor * (diffusionScale + AMBIENT_MULTIPLIER);
    FragColor = vec4(fColor * lightColorMultiplier, 1.0f);
}
