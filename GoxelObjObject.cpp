//
// Created by adrijarch on 3/31/19.
//

#include "GoxelObjObject.hpp"
#include "exceptions/FileNotFoundException.hpp"
#include "exceptions/ParseException.hpp"
#include <cstdio>
#include <cstring>
#include <vector>

GoxelObjObject::GoxelObjObject(const std::string &filename) { // NOLINT(cppcoreguidelines-pro-type-member-init)
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);


  FILE *objfile = fopen(filename.c_str(), "r");
  if (objfile == nullptr)
    throw FileNotFoundException{filename};
  char program[6];
  int major, minor, patch;
  if (!fscanf(objfile, "# %5s %i.%i.%i", program, &major, &minor, &patch) || // NOLINT(cert-err34-c)
      strcmp(program, "Goxel") != 0 || major != 0 || minor != 8 || patch != 2)
    throw ParseException{
        "Provided obj file appears to not have been made by Goxel of supported version. While it might still work, crashing for safety."};

  std::vector<float> vertices {};
  std::vector<unsigned int> indices {};

  parseFile(objfile, vertices, indices);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  indicesCount = indices.size();
}

GoxelObjObject::~GoxelObjObject() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void GoxelObjObject::drawBuffers() const {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

void GoxelObjObject::parseFile(FILE* objfile, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
  char objCmd[3];
  while (!feof(objfile)) {
    fscanf(objfile, "%s", objCmd);
    if (strcmp(objCmd, "v") == 0) {
      float x, y, z, r, g, b;
      fscanf(objfile, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b); // NOLINT(cert-err34-c)
      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);
      vertices.push_back(r);
      vertices.push_back(g);
      vertices.push_back(b);
    } else if (strcmp(objCmd, "vn") == 0) {
      fscanf(objfile, "%*i %*i %*i"); //ignore normals for now
    } else if (strcmp(objCmd, "f") == 0) {
      unsigned int a, b, c, d;
      fscanf(objfile, "%u//%*u %u//%*u %u//%*u %u//%*u", &a, &b, &c, &d); // NOLINT(cert-err34-c)
      // Pushing a, c twice cause need to triangularize
      indices.push_back(a - 1);
      indices.push_back(b - 1);
      indices.push_back(c - 1);
      indices.push_back(a - 1);
      indices.push_back(c - 1);
      indices.push_back(d - 1);
    }
  }
}

