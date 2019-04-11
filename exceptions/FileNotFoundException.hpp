//
// Created by adrijarch on 3/31/19.
//

#ifndef OGLPLAYGROUND_FILENOTFOUNDEXCEPTION_HPP
#define OGLPLAYGROUND_FILENOTFOUNDEXCEPTION_HPP

#include <stdexcept>

/**
 * Tried to open unknown file.
 */
class FileNotFoundException : public std::runtime_error {
  const std::string filename;
public:
  explicit FileNotFoundException(const std::string& filename) : runtime_error("Could not open file " + filename), filename(filename) {}
  /**
   * The name of inaccessible file.
   *
   * This is directly what has been passed in by the creator of this exception.
   *
   * @return The name of the inaccessible file.
   */
  const std::string &getFilename() const { return filename; }
};


#endif //OGLPLAYGROUND_FILENOTFOUNDEXCEPTION_HPP
