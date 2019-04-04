//
// Created by adrijarch on 3/30/19.
//

#ifndef OGLPLAYGROUND_SHADERPROGRAM_HPP
#define OGLPLAYGROUND_SHADERPROGRAM_HPP


#include <string>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class ShaderProgram {
  unsigned int handle;
  std::vector<unsigned int> usedShaders;
  bool isFinished = false;
public:
  ShaderProgram();
  /**
   * Attaches a shader to the current program
   * @param shaderName Name of the shader located in `shaders` dir, without suffix
   * @param shaderType Type of the shader (GL_VERTEX_SAHDER vs GL_FRAGMENT_SHADER)
   * @return self for method chaining.
   * @throws FileNotFoundException
   */
  ShaderProgram& attachShader(const std::string &shaderName, GLenum shaderType);
  /**
   * Finishes adding new shaders, makes itself ready for use.
   * @return self for method chaining.
   */
  ShaderProgram& finish();
  /**
   * Activates this shader program.
   * @return self for method chaining.
   */
  ShaderProgram& activate();

  ShaderProgram& setUniform(const std::string& uniformName, glm::vec4 value);
};


#endif //OGLPLAYGROUND_SHADERPROGRAM_HPP
