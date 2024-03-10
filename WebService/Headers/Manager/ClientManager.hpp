#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "../Core/Client.hpp"
#include <map>
#include <sys/_types/_fd_def.h>

using namespace std;
class ClientManager {
public:
  static map<int, Client> clients;
  void OnConnect(int fd);
  void OnDisConnect(int fd);
  void CheckEvent(int maxFd, fd_set errorEvent, fd_set readEvent,
                  fd_set writeEvent);
};

#endif