#ifndef STRINGFORMAT_HPP
#define STRINGFORMAT_HPP

#include <cstdarg>
#include <sstream>
#include <string>
using namespace std;
class StringFormat {
private:
  string str;

public:
  const char *GetString();
  StringFormat &operator=(const string str);
  string Format(const char *format, ...);
};

#endif