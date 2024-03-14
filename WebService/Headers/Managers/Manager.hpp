#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "ClientManager.hpp"
#include "ResponseManager.hpp"
#include <map>

using namespace std;
class Manager {
public:
  static void Init();
  static ClientManager Client;
  static ResponseManager Response;
};

#endif