#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <iostream>
#include <string>
using namespace std;

// _LIBCPP_INLINE_VISIBILITY exception() _NOEXCEPT {}
// virtual ~exception() _NOEXCEPT;
// virtual const char *what() const _NOEXCEPT;
class CustomException : public exception {
private:
  string errorMsg;

public:
  CustomException(const string msg);
  const char *what() const throw();
  ~CustomException() throw();
};

#define FT_THROW(message, exception)                                           \
  do {                                                                         \
    webserv::ThrowException(__FILE__, __LINE__, message);                      \
    throw CustomException(exception);                                          \
  } while (0)

namespace webserv {
void ThrowException(const string &file, int line, const string &message);
}

#endif