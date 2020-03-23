//
// Created by adriFedora on 13.10.19.
//

#include <vector>
#include "HandWrittenObject.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>

void HandWrittenObject::drawBuffers() const {
glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, verticeCount);
  glBindVertexArray(0);
}

HandWrittenObject::HandWrittenObject(const std::string &filename) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  printf("a\n");
auto vertices = parseFile(fopen(filename.c_str(), "rb"));
  printf("a\n");
  verticeCount = vertices.size();
  printf("a\n");
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);
  printf("a\n");
}

HandWrittenObject::~HandWrittenObject() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

std::vector<float> HandWrittenObject::parseFile(FILE *file) {
  std::vector<float> points{};
  std::vector<unsigned int> triangles{};
  std::vector<float> vertices{};
  while (!feof(file)) {
    char tmp[128];
    fscanf(file, "%s", tmp);
    if (tmp[0] == 'p') {
      float a, b, c;
      fscanf(file, "%f %f %f", &a, &b, &c);
      points.push_back(a);
      points.push_back(b);
      points.push_back(c);
    }
    if (tmp[0] == 't') {
      unsigned int a, b, c;
      fscanf(file, "%u %u %u", &a, &b, &c);
      triangles.push_back(a);
      triangles.push_back(b);
      triangles.push_back(c);
    }
    printf("%s\n", tmp);
  }
  for (unsigned long i = 0; i < triangles.size(); i-=-3) {
    glm::vec3 v1 {points[triangles[i] * 3], points[triangles[i] * 3 + 1], points[triangles[i] * 3 + 2]};
    glm::vec3 v2 {points[triangles[i + 1] * 3], points[triangles[i + 1] * 3 + 1], points[triangles[i + 1] * 3 + 2]};
    glm::vec3 v3 {points[triangles[i + 2] * 3], points[triangles[i + 2] * 3 + 1], points[triangles[i + 2] * 3 + 2]};
    glm::vec3 b = v2 - v1;
    glm::vec3 a = v3 - v1;
    glm::vec3 norm = glm::normalize(glm::cross(a, b));
    vertices.push_back(v1.x);
    vertices.push_back(v1.y);
    vertices.push_back(v1.z);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(norm.x);
    vertices.push_back(norm.y);
    vertices.push_back(norm.z);
    vertices.push_back(v2.x);
    vertices.push_back(v2.y);
    vertices.push_back(v2.z);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(norm.x);
    vertices.push_back(norm.y);
    vertices.push_back(norm.z);
    vertices.push_back(v3.x);
    vertices.push_back(v3.y);
    vertices.push_back(v3.z);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(norm.x);
    vertices.push_back(norm.y);
    vertices.push_back(norm.z);

    vertices.push_back(v1.x);
    vertices.push_back(v1.y);
    vertices.push_back(v1.z);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-norm.x);
    vertices.push_back(-norm.y);
    vertices.push_back(-norm.z);
    vertices.push_back(v3.x);
    vertices.push_back(v3.y);
    vertices.push_back(v3.z);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-norm.x);
    vertices.push_back(-norm.y);
    vertices.push_back(-norm.z);
    vertices.push_back(v2.x);
    vertices.push_back(v2.y);
    vertices.push_back(v2.z);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-norm.x);
    vertices.push_back(-norm.y);
    vertices.push_back(-norm.z);
  }
  return vertices;
}
