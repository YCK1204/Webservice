#include "../../Headers/Contents/Http.hpp"
#include "../../Headers/Utils/Util.hpp"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ios>
#include <sys/socket.h>

Server::Server() {
  members.port = 0;
  members.rootPath = "";
}
Server::~Server() {}
int Server::GetPort() const { return members.port; }
long Server::GetSize() const { return members.clientBodySize; }
const string Server::GetName() const { return members.serverName; }
const string Server::GetIndexPath() const { return members.indexPath; }
const string Server::GetErrorPath() const { return members.errorPagePath; }
const string Server::GetHost() const { return members.host; }
const string Server::GetRootPath() const { return members.rootPath; }
int Server::GetSocket() const { return sock; }
const string Server::GetImgRootPath() const { return members.imgRootPath; }
const string Server::GetJsRootPath() const { return members.jsRootPath; }
const string Server::GetCssRootPath() const { return members.cssRootPath; }
const Location Server::GetLocation(const string path) {
  vector<Location> location = GetLocation();
  Location ret;

  for (vector<Location>::iterator it = location.begin(); it != location.end();
       it++) {
    if (!it->GetDomainPath().compare(path)) {
      ret = *it;
      break;
    }
  }

  return ret;
}
vector<Location> Server::GetLocation() { return locations; }

void Server::SetServer() {
  int servSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (servSocket < 0)
    SetServerFuncFailed(members.port, "socket func Failed");

  sock = servSocket;
  struct sockaddr_in serv_adr;

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(GetHost().c_str());
  serv_adr.sin_port = htons(GetPort());
  SetAddr(serv_adr);

  int t = 1;
  if ((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &t, sizeof(t))) == -1)
    SetServerFuncFailed(members.port, "setsockopt func Failed");
  if (::bind(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    SetServerFuncFailed(members.port, "bind func Failed");
  if (listen(sock, MAX_CLIENT_SIZE) == -1)
    SetServerFuncFailed(members.port, "listen func Failed");
  if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
    SetServerFuncFailed(members.port, "fcntl func Failed");
}


void Server::SetAddr(struct sockaddr_in &addr) { this->addr = addr; }
void Server::SetPort(const int port) { members.port = port; }
void Server::SetSize(const long size) { members.clientBodySize = size; }
void Server::SetName(const string name) { members.serverName = name; }
void Server::SetIndexPath(const string path) { members.indexPath = path; }
void Server::SetErrorPath(const string path) { members.errorPagePath = path; }
void Server::SetHost(const string host) { members.host = host; }
void Server::SetRootPath(const string path) { members.rootPath = path; }
void Server::AddLocation(Location &location) { locations.push_back(location); }
void Server::SetImgRootPath(const string path) { members.imgRootPath = path; }
void Server::SetJsRootPath(const string path) { members.jsRootPath = path; }
void Server::SetCssRootPath(const string path) { members.cssRootPath = path; }