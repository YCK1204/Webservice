#ifndef HTTP_HPP
#define HTTP_HPP

#include "Define.hpp"
#include "Exception.hpp"
#include "File.hpp"
#include "Server.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

extern int numOfLine = 0;

class Http {
private:
  vector<Server> servers;
  File file;
  Http();

public:
  Http(const string confPath);
  ~Http();
  const Server GetServer(unsigned short port);
  vector<Server> GetServer();

  void SetServer(const Server &server);
};

#endif