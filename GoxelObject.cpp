//
// Created by adrijarch on 3/31/19.
//

#include "GoxelObject.hpp"
#include "FileNotFoundException.hpp"
#include <cstdio>

GoxelObject::GoxelObject(std::string &filename) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  FILE* objfile = fopen(filename.c_str(), "r");
  if (objfile == nullptr) {
    throw FileNotFoundException{filename};
  }
}

GoxelObject::~GoxelObject() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}
