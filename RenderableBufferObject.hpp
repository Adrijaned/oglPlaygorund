//
// Created by adrijarch on 4/21/19.
//

#ifndef OGLPLAYGROUND_RENDERABLEBUFFEROBJECT_HPP
#define OGLPLAYGROUND_RENDERABLEBUFFEROBJECT_HPP


class RenderableBufferObject {
public:
  /**
   * Draws inner vertex buffers.
   *
   * Expects shader program to be active that has in vertex vec3 on location 0,
   * in color vec3 on location 1 and in normal vec3 on location 2.
   * //TODO normal handling still missing in GoxelObject
   */
  virtual void drawBuffers() const = 0;
};


#endif //OGLPLAYGROUND_RENDERABLEBUFFEROBJECT_HPP
