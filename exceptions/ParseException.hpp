//
// Created by adrijarch on 4/8/19.
//

#ifndef OGLPLAYGROUND_PARSEEXCEPTION_HPP
#define OGLPLAYGROUND_PARSEEXCEPTION_HPP

#include <stdexcept>

/**
 * Data parsing failed.
 *
 * Thrown to indicate invalid data while parsing, e.g. in GLSL code, data files etc.
 */
class ParseException : public std::runtime_error {
public:
  explicit ParseException(const std::string& what_arg) : runtime_error(what_arg) { };
};


#endif //OGLPLAYGROUND_PARSEEXCEPTION_HPP
