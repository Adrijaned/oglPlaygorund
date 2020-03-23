//
// Created by adrijarch on 5/25/19.
//

#include "MyCustomChunk.hpp"
#include <cstdio>
#include <GL/glew.h>
#include "exceptions/FileNotFoundException.hpp"
#include "exceptions/ParseException.hpp"
#include <vector>
#include "exceptions/InvalidDataException.hpp"

void MyCustomChunk::drawBuffers() const {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

MyCustomChunk::MyCustomChunk(short x, short y, short z) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  char filename[46]; // up to six chars per axis + 2 underscores + ".chunk" + null byte + 17 bytes of path
  snprintf(filename, sizeof(filename), "resources/chunks/%d_%d_%d.chunk", x, y, z);
  const auto file = fopen(filename, "rb");
  if (file == nullptr) {
    throw FileNotFoundException{filename};
  }
  fseek(file, 0, SEEK_END);
  if (ftell(file) != 32 * 32 * 64 * 2) {
    long size = ftell(file);
    fclose(file);
    throw ParseException{"Chunk file must be exactly 131072 bytes, is " + std::to_string(size)};
  }
  rewind(file);
  fread(blockData, 2, 32 * 32 * 64, file);
  fclose(file);

  std::vector<float> vertices{};
  std::vector<unsigned int> indices{};
  int faceCount = 0;

  for (int _x = 0; _x < 32; _x++) {
    for (int _y = 0; _y < 64; _y++) {
      for (int _z = 0; _z < 32; _z++) {
        unsigned short blockId = getBlockId(_x, _y, _z);
        if (blockId != 0) {
          if ((unsigned long) blockId >= sizeof(BLOCK_COLORS) / sizeof(uint32_t)) {
            throw InvalidDataException{"Unknown block id, got " + std::to_string(blockId)};
          }
          if (getBlockId(_x - 1, _y, _z) == 0) {
            const auto push_vertex = [&vertices, blockId, x, y, z, _x, _y, _z](float yOffset, float zOffset) {
              vertices.push_back(x * 32 + _x);
              vertices.push_back(y * 64 + _y + yOffset);
              vertices.push_back(z * 32 + _z + zOffset);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0xff0000u) >> 16) / (float) 255);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0x00ff00u) >> 8) / (float) 255);
              vertices.push_back((BLOCK_COLORS[blockId] & 0x0000ffu) / (float) 255);
              vertices.push_back(-1);
              vertices.push_back(0);
              vertices.push_back(0);
            };
            push_vertex(0, 0);
            push_vertex(0, 1);
            push_vertex(1, 1);
            push_vertex(1, 0);
            addIndicesForFace(indices, faceCount);
          }
          if (getBlockId(_x + 1, _y, _z) == 0) {
            const auto push_vertex = [&vertices, blockId, x, y, z, _x, _y, _z](float yOffset, float zOffset) {
              vertices.push_back(x * 32 + _x + 1);
              vertices.push_back(y * 64 + _y + yOffset);
              vertices.push_back(z * 32 + _z + zOffset);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0xff0000u) >> 16) / (float) 255);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0x00ff00u) >> 8) / (float) 255);
              vertices.push_back((BLOCK_COLORS[blockId] & 0x0000ffu) / (float) 255);
              vertices.push_back(1);
              vertices.push_back(0);
              vertices.push_back(0);
            };
            push_vertex(0, 0);
            push_vertex(0, 1);
            push_vertex(1, 1);
            push_vertex(1, 0);
            addIndicesForFace(indices, faceCount);
          }
          if (getBlockId(_x, _y + 1, _z) == 0) {
            const auto push_vertex = [&vertices, blockId, x, y, z, _x, _y, _z](float xOffset, float zOffset) {
              vertices.push_back(x * 32 + _x + xOffset);
              vertices.push_back(y * 64 + _y + 1);
              vertices.push_back(z * 32 + _z + zOffset);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0xff0000u) >> 16) / (float) 255);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0x00ff00u) >> 8) / (float) 255);
              vertices.push_back((BLOCK_COLORS[blockId] & 0x0000ffu) / (float) 255);
              vertices.push_back(0);
              vertices.push_back(1);
              vertices.push_back(0);
            };
            push_vertex(0, 0);
            push_vertex(0, 1);
            push_vertex(1, 1);
            push_vertex(1, 0);
            addIndicesForFace(indices, faceCount);
          }
          if (getBlockId(_x, _y - 1, _z) == 0) {
            const auto push_vertex = [&vertices, blockId, x, y, z, _x, _y, _z](float xOffset, float zOffset) {
              vertices.push_back(x * 32 + _x + xOffset);
              vertices.push_back(y * 64 + _y);
              vertices.push_back(z * 32 + _z + zOffset);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0xff0000u) >> 16) / (float) 255);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0x00ff00u) >> 8) / (float) 255);
              vertices.push_back((BLOCK_COLORS[blockId] & 0x0000ffu) / (float) 255);
              vertices.push_back(0);
              vertices.push_back(-1);
              vertices.push_back(0);
            };
            push_vertex(0, 0);
            push_vertex(0, 1);
            push_vertex(1, 1);
            push_vertex(1, 0);
            addIndicesForFace(indices, faceCount);
          }
          if (getBlockId(_x, _y, _z + 1) == 0) {
            const auto push_vertex = [&vertices, blockId, x, y, z, _x, _y, _z](float xOffset, float yOffset) {
              vertices.push_back(x * 32 + _x + xOffset);
              vertices.push_back(y * 64 + _y + yOffset);
              vertices.push_back(z * 32 + _z + 1);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0xff0000u) >> 16) / (float) 255);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0x00ff00u) >> 8) / (float) 255);
              vertices.push_back((BLOCK_COLORS[blockId] & 0x0000ffu) / (float) 255);
              vertices.push_back(0);
              vertices.push_back(0);
              vertices.push_back(1);
            };
            push_vertex(0, 0);
            push_vertex(0, 1);
            push_vertex(1, 1);
            push_vertex(1, 0);
            addIndicesForFace(indices, faceCount);
          }
          if (getBlockId(_x, _y, _z - 1) == 0) {
            const auto push_vertex = [&vertices, blockId, x, y, z, _x, _y, _z](float xOffset, float yOffset) {
              vertices.push_back(x * 32 + _x + xOffset);
              vertices.push_back(y * 64 + _y + yOffset);
              vertices.push_back(z * 32 + _z);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0xff0000u) >> 16) / (float) 255);
              vertices.push_back(((BLOCK_COLORS[blockId] & 0x00ff00u) >> 8) / (float) 255);
              vertices.push_back((BLOCK_COLORS[blockId] & 0x0000ffu) / (float) 255);
              vertices.push_back(0);
              vertices.push_back(0);
              vertices.push_back(-1);
            };
            push_vertex(0, 0);
            push_vertex(0, 1);
            push_vertex(1, 1);
            push_vertex(1, 0);
            addIndicesForFace(indices, faceCount);
          }
        }
      }
    }
  }

  char counter = 0;
  for (const auto &item : vertices) {
    if (counter++ < 3) printf("%f   ", item);
    if (counter == 6) printf("\n");
    counter %= 6;
  }

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);

  for (const auto &index : indices) {
    printf("%u ", index);
  }
  printf("\n");

  indicesCount = indices.size();
  printf("%d", indicesCount);
}

void MyCustomChunk::addIndicesForFace(std::vector<unsigned int> &indices, int &faceCount) const {
  indices.push_back(faceCount * 4);
  indices.push_back(faceCount * 4 + 2);
  indices.push_back(faceCount * 4 + 1);
  indices.push_back(faceCount * 4);
  indices.push_back(faceCount * 4 + 3);
  indices.push_back(faceCount * 4 + 2);
  faceCount++;
}

unsigned short constexpr MyCustomChunk::getBlockId(char x, char y, char z) {
  if (x < 0 || y < 0 || z < 0 || x >= 32 || y >= 64 || z>= 32) return 0;
  return blockData[32 * 32 * y + 32 * x + z];
}
