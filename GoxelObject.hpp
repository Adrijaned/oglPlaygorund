//
// Created by adrijarch on 3/31/19.
//

#ifndef OGLPLAYGROUND_GOXELOBJECT_HPP
#define OGLPLAYGROUND_GOXELOBJECT_HPP

#include <string>
#include <GL/glew.h>
#include "RenderableBufferObject.hpp"

/**
 * Loads and processes goxel-exported obj model.
 */
class GoxelObject : public RenderableBufferObject {
  GLuint VAO, VBO, EBO; // vertex array object, vertex buffer object, element buffer object
  unsigned int indicesCount;
public:
  /**
   * Creates a new vertex object from a goxel obj file.
   * @param filename Name of the file with the exported goxel obj
   * @param scale All dimensions in model will be multiplied by this.
   * @throws FileNotFoundException when no file was accesible under given filename.
   */
  explicit GoxelObject(const std::string& filename, float scale);
  /**
   * Gets rid of the allocated buffers.
   */
  ~GoxelObject();

  void drawBuffers() const override;
};


#endif //OGLPLAYGROUND_GOXELOBJECT_HPP
