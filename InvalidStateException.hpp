//
// Created by adrijarch on 3/30/19.
//

#ifndef OGLPLAYGROUND_INVALIDSTATEEXCEPTION_HPP
#define OGLPLAYGROUND_INVALIDSTATEEXCEPTION_HPP

#include <stdexcept>
#include <string>

class InvalidStateException : public std::logic_error {
public:
  explicit InvalidStateException(const std::string& what_arg) : logic_error(what_arg) {};
};


#endif //OGLPLAYGROUND_INVALIDSTATEEXCEPTION_HPP
