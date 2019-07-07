//
// Created by adrijarch on 5/25/19.
//

#ifndef OGLPLAYGROUND_MYCUSTOMCHUNK_HPP
#define OGLPLAYGROUND_MYCUSTOMCHUNK_HPP

#include <cstdint>
#include "RenderableBufferObject.hpp"
#include <vector>

class MyCustomChunk : public RenderableBufferObject {
  unsigned short blockData[32*32*64];
  unsigned int VAO, VBO, EBO; // vertex array object, vertex buffer object, element buffer object
  unsigned short constexpr getBlockId(char x, char y, char z);
  unsigned int indicesCount;
  void addIndicesForFace(std::vector<unsigned int> &indices, int &faceCount) const;
public:
  //contains 0 for blockId 0 - nonexistent
  static constexpr unsigned int BLOCK_COLORS[] = {0, 0xff0000, 0x00ff00, 0x0000ff};
  MyCustomChunk(short x, short y, short z);

  void drawBuffers() const override;
};


#endif //OGLPLAYGROUND_MYCUSTOMCHUNK_HPP
