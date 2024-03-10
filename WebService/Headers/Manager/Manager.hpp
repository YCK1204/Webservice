#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "ClientManager.hpp"
#include "SessionManager.hpp"
#include <map>

using namespace std;
class Manager {
public:
  static ClientManager Client;
  static SessionManager Session;
};

#endif