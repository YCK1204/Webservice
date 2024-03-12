#ifndef HTTP_HPP
#define HTTP_HPP

#include "../Core/StringFormat.hpp"
#include "../Managers/Manager.hpp"
#include "../Utils/Define.hpp"
#include "../Utils/Exception.hpp"
#include "../Utils/FileStream.hpp"
#include "Server.hpp"

using namespace std;

class Http;

extern Http http;

class Http {
private:
  vector<Server> servers;
  fd_set readEvent, writeEvent, errorEvent;
  FileStream file;
  void SetServers();
  void RunServers();
  void HandleErrEvent(int fd);
  void HandleReadEvent(int fd);
  void HandleWriteEvent(int fd);
  void Update();

public:
  StringFormat html;
  StringFormat responseMsgHeaders;
  Http();
  void StartWebService(const string confPath);
  ~Http();
  const Server GetServer(unsigned short sock);
  const Server GetServer(int port);
  vector<Server> GetServer();
};

void PrintConfig(Http &http);

#endif