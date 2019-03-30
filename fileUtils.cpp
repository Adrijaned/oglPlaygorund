//
// Created by adrijarch on 3/19/19.
//

#include "fileUtils.hpp"
#include <string>
#include <cstdio>
char* readFile(const std::string &filename){
  FILE* fp = fopen(filename.c_str(), "r");
  fseek(fp, 0L, SEEK_END);
  auto fileSize = static_cast<size_t>(ftell(fp));
  char* oStr = (char*)malloc(fileSize + 1);
  oStr[fileSize] = 0;
  rewind(fp);
  fread(oStr, 1, fileSize, fp);
  fclose(fp);
  return oStr;
}