//
// Created by adrijarch on 5/26/19.
//

#ifndef OGLPLAYGROUND_INVALIDDATAEXCEPTION_HPP
#define OGLPLAYGROUND_INVALIDDATAEXCEPTION_HPP

#include <stdexcept>

/**
 * Marks any case where data has not been as expected.
 */
class InvalidDataException : public std::runtime_error {
public:
  explicit InvalidDataException(const std::string &arg) : runtime_error(arg) { }
};


#endif //OGLPLAYGROUND_INVALIDDATAEXCEPTION_HPP
