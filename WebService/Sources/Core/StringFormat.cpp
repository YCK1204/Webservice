#include "../../Headers/Core/StringFormat.hpp"
#include "../../Headers/Utils/Util.hpp"
#include <cstdarg>
#include <exception>

string FormatString(const string seperator, string str, const string s1) {
  size_t start = 0;
  size_t end = 0;
  while (true) {
    end = str.find(seperator);
    if (end == string::npos)
      break;
    start = end;
    end += 3;
    str.erase(start, end - start);
    str.insert(start, s1);
  }
  return str;
}

StringFormat &StringFormat::operator=(const string str) {
  this->str = str;

  return *this;
}

string StringFormat::Format(const char *format, ...) {
  string str = format;
  va_list args;
  int cnt = 1;

  va_start(args, format);

  try {

    while (true) {
      if (str.find("{" + IntToString(cnt) + "}") == string::npos)
        break;
      const char *a = va_arg(args, const char *);
      string arg = a;
      str = FormatString("{" + IntToString(cnt) + "}", str, arg);
      cnt++;
    }
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }

  va_end(args);
  return str;
}
const char *StringFormat::GetString() { return this->str.c_str(); }
