//
// Created by adrijarch on 3/31/19.
//

#ifndef OGLPLAYGROUND_GOXELOBJECT_HPP
#define OGLPLAYGROUND_GOXELOBJECT_HPP

#include <string>
#include <GL/glew.h>

/**
 * Loads and processes goxel-exported obj model.
 */
class GoxelObject {
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
  /**
   * Draws inner vertex buffers.
   *
   * Expects shader program to be active that has in vertex vec3 on location 0
   * and in color vec3 on location 1.
   */
  void drawBuffers() const;
};


#endif //OGLPLAYGROUND_GOXELOBJECT_HPP
