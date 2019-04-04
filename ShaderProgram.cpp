//
// Created by adrijarch on 3/30/19.
//

#include "ShaderProgram.hpp"
#include "fileUtils.hpp"
#include "InvalidStateException.hpp"
#include <cstdio>

ShaderProgram& ShaderProgram::attachShader(const std::string &shaderName, GLenum shaderType) {
  if (isFinished) {
    throw InvalidStateException{"Attaching shader to already finished program!"};
  }
  GLchar* shaderSource = readFile("shaders/" + shaderName + ".glsl");
  unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderSource, nullptr); // yep, we are passing pointer to pointer
  glCompileShader(shader);
  free(shaderSource);
  int compileStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  if (!compileStatus) {
    char shaderLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, shaderLog);
    printf("ERROR::SHADER::COMPILE::FAILED\n%s", shaderLog);
  }
  glAttachShader(this->handle, shader);
  usedShaders.push_back(shader);
  return *this;
}

ShaderProgram::ShaderProgram() {
  handle = glCreateProgram();
}

ShaderProgram &ShaderProgram::finish() {
  if (isFinished) {
    throw InvalidStateException{"Program has already been finished!"};
  }
  glLinkProgram(handle);
  for (const auto shader : usedShaders) {
    glDeleteShader(shader);
  }
  isFinished = true;
  return *this;
}

ShaderProgram &ShaderProgram::activate() {
  if (!isFinished) {
    throw InvalidStateException{"Program has not been finished yet!"};
  }
  glUseProgram(handle);
  return *this;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &uniformName, glm::vec4) {
  GLint uniformLocation = glGetUniformLocation(handle, uniformName.c_str());
  if (uniformLocation == -1)
  return *this;
}
