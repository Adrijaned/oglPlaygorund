//
// Created by adrijarch on 3/31/19.
//

#ifndef OGLPLAYGROUND_FILENOTFOUNDEXCEPTION_HPP
#define OGLPLAYGROUND_FILENOTFOUNDEXCEPTION_HPP

#include <stdexcept>

class FileNotFoundException : public std::runtime_error {
public:
  explicit FileNotFoundException(const std::string& filename) : runtime_error("Could not open file " + filename) {}
};


#endif //OGLPLAYGROUND_FILENOTFOUNDEXCEPTION_HPP
