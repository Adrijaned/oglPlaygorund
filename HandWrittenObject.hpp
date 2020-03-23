//
// Created by adriFedora on 13.10.19.
//

#ifndef OGLPLAYGROUND_HANDWRITTENOBJECT_HPP
#define OGLPLAYGROUND_HANDWRITTENOBJECT_HPP


#include <string>
#include "RenderableBufferObject.hpp"

class HandWrittenObject : public RenderableBufferObject {
private:
  unsigned int VAO, VBO, verticeCount;

  static std::vector<float> parseFile(FILE *file);

public:
  virtual ~HandWrittenObject();

  HandWrittenObject(const std::string &filename);

  void drawBuffers() const override;
};


#endif //OGLPLAYGROUND_HANDWRITTENOBJECT_HPP
