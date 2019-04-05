//
// Created by adrijarch on 4/5/19.
//

#ifndef OGLPLAYGROUND_UNKNOWNIDENTIFIEREXCEPTION_HPP
#define OGLPLAYGROUND_UNKNOWNIDENTIFIEREXCEPTION_HPP

#include <stdexcept>

/**
 * Thrown when trying to access unknown identifier by name.
 *
 * Example usage might include trying to set uniforms in OGL @ref ShaderProgram::setUniform ,
 * or accessing symbols in runtime-loaded libs.
 */
class UnknownIdentifierException : public std::invalid_argument {
public:
  explicit UnknownIdentifierException(const std::string& what_arg) : invalid_argument(what_arg) {}
};


#endif //OGLPLAYGROUND_UNKNOWNIDENTIFIEREXCEPTION_HPP
