#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP

#include "../Core/Session.hpp"
#include <map>
using namespace std;
class SessionManager {
public:
  static map<int, Session> sessions;
};

#endif