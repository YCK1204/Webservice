#include "../../Headers/Http.hpp"
#include "../../Headers/Utils.hpp"

Http::Http(const string confPath) {
  file.SetFile(confPath);

  if (file.ExistFile()) {
    while (!file.IsEof()) {
      Server serv = ParseServer(file.GetFile());
      servers.push_back(serv);
    }
  } else {
    FT_THROW("Is not exist config file (" + confPath + ")", ERR_CONF);
  }
}

const Server Http::GetServer(unsigned short port) {
  vector<Server> server = GetServer();
  Server ret;

  for (vector<Server>::iterator it = server.begin(); it != servers.end();
       it++) {
    if (it->GetPort() == port) {
      ret = *it;
      break;
    }
  }
  return ret;
}

vector<Server> Http::GetServer() { return servers; }
void Http::SetServer(const Server &server) { servers.push_back(server); }
Http::~Http() {}