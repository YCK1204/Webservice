#include "../../Headers/Utils/FileStream.hpp"

fstream &FileStream::GetFile() { return file; }
FileStream::~FileStream() {}
bool FileStream::ExistFile() { return file.is_open(); }
void FileStream::SetFile(std::string path) {
  file.open(path);
  this->path = path;
}

string FileStream::GetLine() {
  string line;

  getline(file, line);
  return line;
}

bool FileStream::IsEof() { return file.eof(); }
