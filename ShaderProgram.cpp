//
// Created by adrijarch on 3/30/19.
//

#include "ShaderProgram.hpp"
#include "fileUtils.hpp"
#include "exceptions/InvalidStateException.hpp"
#include "exceptions/UnknownIdentifierException.hpp"
#include <cstdio>
#include <glm/gtc/type_ptr.hpp>

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

ShaderProgram &ShaderProgram::setUniform(const std::string &uniformName, const glm::vec4& value) {
  glUniform4f(getUniformLocation(uniformName), value.x, value.y, value.z, value.w);
  return *this;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &uniformName, const glm::vec3& value) {
  glUniform3f(getUniformLocation(uniformName), value.x, value.y, value.z);
  return *this;
}

GLuint ShaderProgram::getUniformLocation(const std::string& uniformName) const {
  GLint uniformLocation = glGetUniformLocation(handle, uniformName.c_str());
  if (uniformLocation == -1) throw UnknownIdentifierException{"Uniform name not found."};
  return uniformLocation;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &uniformName, const glm::mat4 &value) {
  glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
  return *this;
}
