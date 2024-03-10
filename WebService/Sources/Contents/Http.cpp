#include "../../Headers/Contents/Http.hpp"
#include "../../Headers/Utils/Utils.hpp"
#include <sys/socket.h>
#include <vector>

Http::Http(const string confPath) {
  file.SetFile(confPath);

  numOfLine = 0;
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
  // PrintConfig(*this);
  // run server
  if (servers.size() > 0) {
    SetServers();
    RunServers();
  }
}

void Http::SetServers() {
  vector<Server> server;

  FD_ZERO(&event);
  for (vector<Server>::iterator it = server.begin(); it != server.end(); it++) {
    it->SetServer();
    FD_SET(it->GetSocket(), &event);
    maxFd = it->GetSocket();
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

const Server Http::GetServer(int sock) {
  vector<Server> server = GetServer();
  Server ret;

  for (vector<Server>::iterator it = server.begin(); it != servers.end();
       it++) {
    if (it->GetSocket() == sock) {
      ret = *it;
      break;
    }
  }
  return ret;
}

void Http::RunServers() {
  struct timeval timer;

  timer.tv_sec = 1;
  timer.tv_usec = 0;
  while (true) {
    readEvent = event;
    errorEvent = event;
    if ((select(maxFd + 1, &readEvent, 0, &errorEvent, &timer)) < 0)
      FT_THROW("An error occurs during servers run", "select func Failed");
    HandleClient();
  }
}

void Http::HandleClient() {
  Manager::Client.CheckEvent(maxFd, errorEvent, readEvent, writeEvent);

  for (map<int, ClientData>::iterator it = clients.begin(); it != clients.end();
       it++) {
    if ((time(NULL) - it->second.last_active_times) > TIMEOUT) {
      disconnectClient(it->first);
      break;
    }
  }
}

void Http::HandleErrEvent(int fd) {
  vector<Server> server = GetServer();

  for (vector<Server>::iterator it = server.begin(); it != server.end(); it++) {
    if (fd == it->GetSocket())
      FT_THROW(IntToString(it->GetPort()) + "Port server socket error",
               "The server socket occured error event");
  }
  cerr << "Client socket error" << endl;
  Manager::Client.OnDisConnect(fd);
}

void Http::HandleReadEvent(int fd) {
  bool isConnecting = false;
  int servSock = 0;
  vector<Server> server = GetServer();

  // Check connect client
  for (vector<Server>::iterator it = server.begin(); it != server.end(); it++) {
    if (it->GetPort() == fd) {
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

    Manager::Client.OnConnect(fd);
    Manager::Client.clients[clientSock].data.fd = clientSock;
  } else {
    Manager::Client.clients[fd].Read();
  }
}
void Http::HandleWriteEvent(int fd) {}
vector<Server> Http::GetServer() { return servers; }
Http::~Http() {}

void PrintConfig(Http &http) {
  vector<Server> server = http.GetServer();

  for (vector<Server>::iterator it = server.begin(); it != server.end(); it++) {
    cout << "server {\n";
    cout << "   listen " << it->GetPort() << endl;
    cout << "   server_name " << it->GetName() << endl;
    cout << "   root " << it->GetRootPath() << endl;
    cout << "   client_body_size " << it->GetSize() << endl;
    cout << "   index " << it->GetIndexPath() << endl;
    cout << "   error_page " << it->GetErrorPath() << endl;
    cout << "   host " << it->GetHost() << endl;
    vector<Location> location = it->GetLocation();
    for (vector<Location>::iterator it = location.begin(); it != location.end();
         it++) {
      cout << "       location " << it->GetDomainPath() << " {" << endl;
      cout << "            allow_methods ";
      if (it->GetMethod(GET))
        cout << "GET ";
      if (it->GetMethod(POST))
        cout << "POST ";
      if (it->GetMethod(DELETE))
        cout << "DELETE ";
      cout << endl;
      if (!it->GetRootPath().empty())
        cout << "           root " << it->GetRootPath() << endl;
      cout << "          autoindex " << it->GetIsAutoIndex() << endl;
      cout << "          index " << it->GetIndexPath() << endl;
      cout << "          return " << it->GetReturnPath() << endl;
      cout << "       }" << endl;
    }
    cout << "}" << endl;
  }
}
