#ifndef FILE_HPP
#define FILE_HPP

#include "Util.hpp"

class FileStream {
private:
  fstream file;
  string path;

public:
  fstream &GetFile();
  ~FileStream();
  void SetFile(std::string path);
  bool ExistFile();
  bool IsEof();
  string GetLine();
  std::string name;
  off_t size;
  time_t lastModified;
  bool is_dir;
  FileStream() {}
  FileStream(const FileStream &other) { *this = other; }

  FileStream &operator=(const FileStream &other) {
    if (this != &other) {
      this->file.open(path);
    }
    return *this;
  }
};

#endif