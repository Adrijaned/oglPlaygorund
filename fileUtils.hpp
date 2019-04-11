//
// Created by adrijarch on 3/19/19.
//

#ifndef OGLPLAYGROUND_FILEUTILS_HPP
#define OGLPLAYGROUND_FILEUTILS_HPP

#include <GL/glew.h>
#include <string>

/**
 * Returns file in heap allocated cstring.
 *
 * File is returned in heap-allocated space, to prevent memory leaks the memory must be manually
 * freed [using free()] when no longer needed.
 *
 * @param filename Name and path of the file to get
 * @return Pointer to cstring with the contents of the file.
 * @throws FileNotFoundException when no file was accessible under given filename.
 */
char* readFile(const std::string &filename);

#endif //OGLPLAYGROUND_FILEUTILS_HPP
