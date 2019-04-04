//
// Created by adrijarch on 3/31/19.
//

#ifndef OGLPLAYGROUND_GOXELOBJECT_HPP
#define OGLPLAYGROUND_GOXELOBJECT_HPP

#include <string>
#include <GL/glew.h>

class GoxelObject {
  GLuint VAO, VBO, EBO; // vertex array object, vertex buffer object, element buffer object
public:
  /// Creates a new object from a goxel obj file.
  /// \param filename filename of the obj file
  GoxelObject(std::string& filename);
  ~GoxelObject();
};


#endif //OGLPLAYGROUND_GOXELOBJECT_HPP
