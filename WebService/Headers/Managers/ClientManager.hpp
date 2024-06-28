#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "../Core/Client.hpp"
#include <sys/_types/_fd_def.h>
#include <vector>

using namespace std;
class ClientManager {
public:
  static vector<Client> clients;
  static void OnConnect(int fd);
  static void OnDisConnect(int fd);
  static void OnRead(int numOfByte, int fd);
  static void OnWrite(int numOfByte, int fd);
  static void Update();
  static void UpdateState(fd_set &readEvent, fd_set &errorEvent);
  static void CheckTimeOut();
  static int GetMostOfClientFd();
  static int FindClientIndex(int fd);
};

#endif