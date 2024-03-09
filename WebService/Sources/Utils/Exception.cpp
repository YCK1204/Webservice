#include "../../Headers/Exception.hpp"

CustomException::CustomException(const string msg) { errorMsg = msg; }

CustomException::~CustomException() throw() {}

const char *CustomException::what() const throw() { return errorMsg.c_str(); }

void webserv::ThrowException(const string &file, int line,
                             const string &message) {
  cerr << file << ":" << line << " " + message << endl;
}

void serverFunctionExecuteFailed(string msg, string detail) {
  FT_THROW(msg + "[" + static_cast<const string>(strerror(errno)) + "]",
           CustomException(detail));
}
