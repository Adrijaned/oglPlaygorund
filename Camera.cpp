#include <cmath>

//
// Created by adrijarch on 5/11/19.
//

#include "Camera.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>

const glm::mat4 Camera::getView() {
  if (dirty) {
    glm::vec3 rotationVec;
    const auto xzMultiplier = std::cos(pitch);
    rotationVec.x = std::cos(yaw) * xzMultiplier;
    rotationVec.z = std::sin(yaw) * xzMultiplier;
    rotationVec.y = std::sin(pitch);

    viewMatrix = glm::lookAt(position, rotationVec, glm::vec3{0, 1, 0});
    dirty = false;
  }
  return viewMatrix;
}

Camera &Camera::changeYaw(float value) {
  yaw = fmod(yaw + value, 2 * M_PI);
  if (yaw < 0) {
    yaw += 2 * M_PI;
  }
  dirty = true;
  return *this;
}

Camera &Camera::changePitch(float value) {
  pitch = std::clamp<float>(pitch + value, -M_PI_2, M_PI_2);
  dirty = true;
  return *this;
}
