#include "../../Headers/Contents/Http.hpp"
#include "../../Headers/Utils/Util.hpp"

vector<Client> ClientManager::clients;
map<string, string> ResponseManager::type;
map<int, string> ResponseManager::status;

Http::Http() {
  html = "<!DOCTYPE html>\
<html>\
  <head>\
    {1}\
  </head>\
  <body>\
    {2}\
  </body>\
</html>";

  responseMsgHeaders = "HTTP/1.1 {1} {2}\r\n\
Accept-language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n\
Cache-Control:no-cache=Set-Cookie\r\n\
Connection: close\r\n\
Content-Length: {3}\r\n\
Content-Type: {4}; charset=utf-8\r\n\
Date: {5}\r\n\
keep-alive: timeout= {6}, max= {7}\r\n\
Last-Modified: {8}\r\n\
";
}

void Http::StartWebService(const string confPath) {
  file.SetFile(confPath);

  numOfLine = 0;
  maxFd = 0;
  responseStatus = 0;
  if (file.ExistFile()) {
    while (!file.IsEof()) {
      string line;
      numOfLine++;
      getline(file.GetFile(), line);
      line = trim(line);
      if (line.empty())
        continue;
      Server serv = ParseServer(file.GetFile());
      CheckValidServer(serv);
      servers.push_back(serv);
    }
  } else {
    FT_THROW("Is not exist config file (" + confPath + ")", ERR_CONF);
  }
  if (servers.size() > 0) {
    SetServers();
    RunServers();
  }
}

void Http::SetServers() {
  FD_ZERO(&event);
  for (vector<Server>::iterator it = servers.begin(); it != servers.end();
       it++) {
    it->SetServer();
    FD_SET(it->GetSocket(), &event);
    maxFd = it->GetSocket();
  }
}

const Server Http::GetServer(unsigned short sock) {
  Server ret;

  for (vector<Server>::iterator it = servers.begin(); it != servers.end();
       it++) {
    if (it->GetSocket() == sock) {
      ret = *it;
      break;
    }
  }
  return ret;
}

const Server Http::GetServer(int port) {
  Server ret;

  for (vector<Server>::iterator it = servers.begin(); it != servers.end();
       it++) {
    if (it->GetPort() == port) {
      ret = *it;
      break;
    }
  }
  return ret;
}

void Http::RunServers() {
  struct timeval timer;

  timer.tv_sec = 2;
  timer.tv_usec = 0;
  while (true) {
    readEvent = event;
    writeEvent = event;
    errorEvent = event;
    if ((select(maxFd + 1, &readEvent, &writeEvent, &errorEvent, &timer)) < 0)
      FT_THROW("An error occurs during servers run", "select func Failed");
    Update();
  }
}

void Http::Update() {
  for (int i = 0; i <= maxFd; i++) {
    if (FD_ISSET(i, &errorEvent)) {
      HandleErrEvent(i);
    } else if (FD_ISSET(i, &readEvent)) {
      HandleReadEvent(i);
    }
  }

  Manager::Client.UpdateState(readEvent, errorEvent);
  Manager::Client.Update();
}

void Http::HandleErrEvent(int fd) {
  for (vector<Server>::iterator it = servers.begin(); it != servers.end();
       it++) {
    if (fd == it->GetSocket())
      FT_THROW(IntToString(it->GetPort()) + "Port server socket error",
               "The server socket occured error event");
  }
}

void Http::HandleReadEvent(int fd) {
  bool isConnecting = false;
  int servSock = 0;

  for (vector<Server>::iterator it = servers.begin(); it != servers.end();
       it++) {
    if (it->GetSocket() == fd) {
      isConnecting = true;
      servSock = it->GetSocket();
      break;
    }
  }

  if (isConnecting) {
    int clientSock = accept(servSock, NULL, NULL);
    if (clientSock < 0)
      FT_THROW(IntToString(GetServer(servSock).GetPort()) +
                   "Server can not accept",
               "accept func Failed");

    Manager::Client.OnConnect(clientSock);
  }
}

vector<Server> Http::GetServer() { return servers; }
Http::~Http() {}
