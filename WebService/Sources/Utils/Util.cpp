#include "../../Headers/Utils.hpp"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) { return rtrim(ltrim(s)); }

string StringToLower(string str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (str[i] >= 65 && str[i] <= 90)
      str[i] += 32;
  }

  return str;
}

bool IsRemaingString(stringstream &ss) {
  string str;
  ss >> str;

  if (str[0] == '#')
    return false;
  return !str.empty();
}

string IntToString(int n) {
  string ret;
  int len = 1;
  int tmp = n;

  while ((tmp /= 10))
    len++;

  for (int i = len - 1; i >= 0; i++) {
    string a;
    a[0] = n % 10 + '0';
    ret.insert(0, a);
    n /= 10;
  }

  return ret;
}

bool IsExistFolder(string path) {
  DIR *dir;

  dir = opendir(path.c_str());
  return dir != NULL;
}

bool IsExistFile(string path) {
  ifstream file(path);

  return file.is_open();
}
