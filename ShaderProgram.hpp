//
// Created by adrijarch on 3/30/19.
//

#ifndef OGLPLAYGROUND_SHADERPROGRAM_HPP
#define OGLPLAYGROUND_SHADERPROGRAM_HPP


#include <string>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

/**
 * Abstraction layer over OGL shader programs.
 *
 * Provides methods for handy loading of shaders from files and using them,
 * without having to deal with OGL pointers.
 */
class ShaderProgram {
  /**
   * OGL pointer the the OGL ShaderProgram.
   */
  unsigned int handle;
  /**
   * Shaders linked together in this program.
   *
   * Used for deleting used shaders after program is compiled.
   */
  std::vector<unsigned int> usedShaders;
  /**
   * Has this program been compiled yet.
   *
   * Used for throwing nice errors when trying to modify compiled program/use uncompiled.
   */
  bool isFinished = false;
  /**
   * Retrieves uniform location from the shader for further use.
   * @param uniformName Name of the uniform to retrieve location of.
   * @return Location of the unifomr.
   * @throws UnknownIdentifierException when no uniform with specified name was found.
   */
  GLuint getUniformLocation(const std::string& uniformName) const;
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
  ///@{
  /**
   * Sets a value of uniform in shader.
   *
   * The shader must be active for this to have effect, failure to ensure so will however NOT result in an Exception.
   *
   * @param uniformName Name of the uniform value
   * @param value The value to set
   * @return self for method chaining.
   * @throws UnknownIdentifierException when no uniform with specified name was found.
   */
  ShaderProgram& setUniform(const std::string& uniformName, const glm::vec4& value);
  ShaderProgram& setUniform(const std::string& uniformName, const glm::vec3& value);
  ///@}
};


#endif //OGLPLAYGROUND_SHADERPROGRAM_HPP
