#include "../../Headers/Http.hpp"

Server::Server() { port = 0; }
Server::~Server() {}
int Server::GetPort() const { return port; }
long Server::GetSize() const { return clientBodySize; }
const string Server::GetName() const { return serverName; }
const string Server::GetIndexPath() const { return defaultIndexPath; }
const string Server::GetErrorPath() const { return errorPagePath; }
const string Server::GetHost() const { return host; }
const string Server::GetRootPath() const { return rootPath; }
const Location Server::GetLocation(const string path) {
  vector<Location> location = GetLocation();
  Location ret;

  for (vector<Location>::iterator it = location.begin(); it != location.end();
       it++) {
    if (!it->GetRootPath().compare(path)) {
      ret = *it;
      break;
    }
  }

  return ret;
}
vector<Location> Server::GetLocation() { return locations; }

void Server::SetPort(const int port) { this->port = port; }
void Server::SetSize(const long size) { clientBodySize = size; }
void Server::SetName(const string name) { serverName = name; }
void Server::SetIndexPath(const string path) { defaultIndexPath = path; }
void Server::SetErrorPath(const string path) { errorPagePath = path; }
void Server::SetHost(const string host) { this->host = host; }
void Server::SetRootPath(const string path) { this->rootPath = path; }
void Server::AddLocation(Location &location) { locations.push_back(location); }