#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "ClientManager.hpp"
#include "ResponseManager.hpp"
#include "SessionManager.hpp"
#include <map>

using namespace std;
class Manager {
public:
  static void Init();
  static ClientManager Client;
  static SessionManager Session;
  static ResponseManager Response;
};

#endif