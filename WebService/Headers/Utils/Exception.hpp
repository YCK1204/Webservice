#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <iostream>
#include <string>
using namespace std;

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
void SetServerFuncFailed(int port, string detail);
void IsNotValidServer(int port, string detail);
void IsNotValidLocation(string path, string detail);
#endif