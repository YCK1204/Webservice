#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Utils/Define.hpp"

class Client {
public:
  CLIENT_DATA data;
  Client();
  void Read();
};

#endif