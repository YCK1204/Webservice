#ifndef HTTP_HPP
#define HTTP_HPP

#include "../Manager/Manager.hpp"
#include "../Utils/Define.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/File.hpp"
#include "Server.hpp"

using namespace std;

extern int numOfLine;

class Http {
private:
  int maxFd;
  vector<Server> servers;
  fd_set event, readEvent, writeEvent, errorEvent;
  File file;
  Http();
  void SetServers();
  void RunServers();
  void HandleClient();
  void HandleErrEvent(int fd);
  void HandleReadEvent(int fd);
  void HandleWriteEvent(int fd);

public:
  Http(const string confPath);
  ~Http();
  const Server GetServer(unsigned short port);
  const Server GetServer(int sock);
  vector<Server> GetServer();
};

void PrintConfig(Http &http);

#endif