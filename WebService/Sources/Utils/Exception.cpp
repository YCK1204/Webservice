#include "../../Headers/Utils/Exception.hpp"
#include "../../Headers/Utils/Util.hpp"

CustomException::CustomException(const string msg) { errorMsg = msg; }

CustomException::~CustomException() throw() {}

const char *CustomException::what() const throw() { return errorMsg.c_str(); }

void webserv::ThrowException(const string &file, int line,
                             const string &message) {
  cerr << file << ":" << line << " " << message << endl;
}

void SetServerFuncFailed(int port, string detail) {
  FT_THROW("Set " + IntToString(port) + " Port Server Failed " + "[" +
               static_cast<const string>(strerror(errno)) + "]",
           CustomException(detail));
}

void IsNotValidServer(int port, string detail) {
  FT_THROW(IntToString(port) + " Port server member variable has not been set ",
           CustomException(detail));
}

void IsNotValidLocation(string path, string detail) {
  FT_THROW("Is not valid loation domain path (" + path + ") ",
           CustomException(detail));
}