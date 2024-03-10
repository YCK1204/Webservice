#include "../../Headers/Exception.hpp"
#include "../../Headers/Utils/Utils.hpp"

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
  if (!str.compare("{")) {
    str.clear();
    ss >> str;
  }
  return !str.empty();
}

string IntToString(int n) {
  string ret;
  int len = 1;
  int tmp = n;

  while ((tmp /= 10))
    len++;

  for (int i = len - 1; i >= 0; i--) {
    string a;
    a += n % 10 + '0';
    ret.insert(0, a);
    n /= 10;
  }
  return ret;
}

bool IsExistFolder(string path) {
  DIR *dir;

  dir = opendir(path.c_str());
  if (dir != NULL) {
    closedir(dir);
    return true;
  }
  return false;
}

bool IsExistFile(string path) {
  ifstream file(path);

  if (IsExistFolder(path))
    return false;
  if (file.is_open()) {
    file.close();
    return true;
  }
  return false;
}

string ExtractWithComments(stringstream &ss) {
  string ret;

  ss >> ret;

  size_t i = ret.find('#');
  if (i != string::npos)
    ret = ret.substr(0, i);
  return ret;
}

string ExtractWithComments(string str) {
  size_t i = str.find('#');
  if (i != string::npos)
    str = str.substr(0, i);
  return str;
}

void CheckValidServer(const Server &serv) {
  if (serv.GetPort() == 0)
    IsNotValidServer(serv.GetPort(), "Port has to be set");
  if (serv.GetRootPath().empty())
    IsNotValidServer(serv.GetPort(), "Root path has to be set");
  if (serv.GetIndexPath().empty())
    IsNotValidServer(serv.GetPort(), "Index path has to be set");
  if (serv.GetHost().empty())
    IsNotValidServer(serv.GetPort(), "Host address has to be set");
}