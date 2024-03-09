#ifndef FILE_HPP
#define FILE_HPP

#include "Utils.hpp"

class File {
private:
  fstream file;

public:
  fstream &GetFile();
  ~File();
  void SetFile(std::string path);
  bool ExistFile();
  bool IsEof();
  string GetLine();
};

#endif