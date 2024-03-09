#include "../Headers/File.hpp"

fstream &File::GetFile() { return file; }
File::~File() {}
bool File::ExistFile() { return file.is_open(); }
void File::SetFile(std::string path) { file.open(path); }

string File::GetLine() {
  string line;

  getline(file, line);
  return line;
}

bool File::IsEof() { return file.eof(); }
