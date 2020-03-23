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

    viewMatrix = glm::lookAt(position, position + rotationVec, glm::vec3{0, 1, 0});
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
  pitch = std::clamp<float>(pitch + value, -M_PI_2 + 0.0001f, M_PI_2 - 0.0001f);
  dirty = true;
  return *this;
}

Camera &Camera::move(const Camera::MovementDirection& direction, float distance) {
  switch (direction) {
    case UP:
      position.y += distance;
      break;
    case DOWN:
      position.y -= distance;
      break;
    case FORWARD:
      position.x += std::cos(yaw) * distance;
      position.z += std::sin(yaw) * distance;
      break;
    case RIGHT:
      position.x -= std::sin(yaw) * distance;
      position.z += std::cos(yaw) * distance;
      break;
    case BACKWARD:
      position.x -= std::cos(yaw) * distance;
      position.z -= std::sin(yaw) * distance;
      break;
    case LEFT:
      position.x += std::sin(yaw) * distance;
      position.z -= std::cos(yaw) * distance;
      break;
  }
  dirty = true;
  return *this;
}

const glm::vec3 &Camera::getPosition() const {
  return position;
}
