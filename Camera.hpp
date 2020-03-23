//
// Created by adrijarch on 5/11/19.
//

#ifndef OGLPLAYGROUND_CAMERA_HPP
#define OGLPLAYGROUND_CAMERA_HPP

#include <glm/glm.hpp>

/**
 * OGL style camera for computing view matrix for use by shaders.
 */
class Camera {
  /**
   * Position of the camera itself in the source coordinate system.
   */
  glm::vec3 position = glm::vec3{0, 0, 0};
  /**
   * Rotation along the y axis, achieved by moving mouse horizontally.
   * Radians normalized in range [0, 2 * PI].
   */
  float yaw = 0;
  /**
   * Rotation in up/down manner, achieved by moving mouse vertically.
   * Radians clamped in range [ - PI / 2, PI / 2 ].
   */
  float pitch = 0;
  /**
   * Denotes whether anything in this class has been changed since last
   * recalculation of \c target.
   * This is handy to speed up calculations in some cases.
   * @see viewMatrix
   */
  bool dirty = true;
  /**
   * The last computed view matrix.
   * This is handy to speed up calculation in some cases.
   * @see dirty
   */
  glm::mat4 viewMatrix{1.0f};
public:

  /**
   * Returns the view matrix from this camera
   * @return The view matrix
   */
  const glm::mat4 getView();

  /**
   * Changes the camera yaw by given value in radians.
   * Yaw is expected to refer to rotation along the vertical/y axis in clockwise
   * manner.
   * @param value Value in radians to change yaw by.
   * @return self for method chaining.
   */
  Camera &changeYaw(float value);

/**
 * Changes the camera pitch by given value in radians.
 * Pitch is expected to refer to rotation in up/down manner / along the
 * horizontal axis ortogonal to direction denoted by yaw, with positive
 * numbers used for the up direction.
 *
 * @warning Resulting pitch value is @b clamped to range @f$
 *  \left\langle-\frac{\pi}{2},\frac{\pi}{2}\right\rangle
 * @f$
 * @param value Value in radians to change pitch by.
 * @return self for method chaining.
 */
  Camera &changePitch(float value);
  /**
   * Possible directions Camera can move in.
   * @see move
   */
  enum MovementDirection {
    UP, DOWN, FORWARD, BACKWARD, LEFT, RIGHT
  };

  const glm::vec3 &getPosition() const;

  /**
   * Moves this camera in given direction relative by current @b yaw.
   * @param direction Direction to move into
   * @param distance Distance to move by
   * @return self for method chaining.
   */
  Camera& move(const MovementDirection& direction, float distance);
};


#endif //OGLPLAYGROUND_CAMERA_HPP
