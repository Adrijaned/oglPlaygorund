//
// Created by adrijarch on 3/31/19.
//

#ifndef OGLPLAYGROUND_GOXELOBJOBJECT_HPP
#define OGLPLAYGROUND_GOXELOBJOBJECT_HPP

#include <string>
#include <vector>
#include <GL/glew.h>
#include "RenderableBufferObject.hpp"
#include <algorithm>
#include <cstring>

/**
 * Loads and processes goxel-exported obj model.
 * @deprecated Does not allow optimizing the models in some ways and is generally annoying to work with
 */
class GoxelObjObject : public RenderableBufferObject {
  GLuint VAO, VBO, EBO; // vertex array object, vertex buffer object, element buffer object
  unsigned int indicesCount;
  static void parseFile(FILE* objfile, std::vector<float>& vertices, std::vector<unsigned int>& indices);
public:
  /**
   * Creates a new vertex object from a goxel obj file.
   * @param filename Name of the file with the exported goxel obj
   * @throws FileNotFoundException when no file was accesible under given filename.
   */
  explicit GoxelObjObject(const std::string &filename);
  /**
   * Gets rid of the allocated buffers.
   */
  ~GoxelObjObject();

  void drawBuffers() const override;
};


#endif //OGLPLAYGROUND_GOXELOBJOBJECT_HPP
