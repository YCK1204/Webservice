#include "../../Headers/Managers/ClientManager.hpp"
#include "../../Headers/Contents/Http.hpp"

int ClientManager::GetMostFdOfClients() {
  vector<Client> &clients = Manager::Client.clients;
  int ret = 0;

  for (size_t i = 0; i < clients.size(); i++) {
    if (clients[i].data.fd > ret)
      ret = clients[i].data.fd;
  }

  return ret;
}

void ClientManager::OnConnect(int fd) {
  CLIENT_DATA data;
  Client client;

  client.data.fd = fd;
  ClientManager::clients.push_back(client);

  maxFd = (fd > maxFd) ? fd : maxFd;
  FD_SET(fd, &event);
  fcntl(fd, F_SETFL, O_NONBLOCK);
}

void ClientManager::UpdateState(fd_set &readEvent, fd_set &errorEvent) {
  vector<Client> &clients = Manager::Client.clients;
  for (size_t i = 0; i < clients.size(); i++) {
    if (FD_ISSET(clients[i].data.fd, &errorEvent))
      clients[i].data.state = ERROR;
    else if (FD_ISSET(clients[i].data.fd, &readEvent))
      clients[i].data.state = READ;
    else if (clients[i].data.state != WRITE)
      clients[i].data.state = NONE;
  }
}

int ClientManager::FindClientIndex(int fd) {
  vector<Client> &clients = Manager::Client.clients;
  int cnt = 0;

  for (size_t i = 0; i < clients.size(); i++) {
    if (clients[i].data.fd == fd)
      break;
    cnt++;
  }
  return cnt;
}

void ClientManager::OnDisConnect(int fd) {
  size_t idx = FindClientIndex(fd);
  vector<Client> &clients = Manager::Client.clients;
  if (idx == clients.size()) {
    return;
  }

  clients.erase(clients.begin() + idx);
  int _maxFd = GetMostFdOfClients();

  if (_maxFd == 0)
    maxFd = http.GetServer().size() + 2;
  else
    maxFd = _maxFd;
  FD_CLR(fd, &event);
  close(fd);
}

void ClientManager::Update() {
  vector<Client> &clients = Manager::Client.clients;

  for (size_t i = 0; i < clients.size(); i++) {
    CLIENT_STATE state = clients[i].data.state;

    switch (state) {
    case ERROR:

      clients[i].UpdateError();
      break;
    case READ:
      clients[i].UpdateRead();
      break;
    case WRITE:
      clients[i].UpdateWrite();
      OnDisConnect(clients[i].data.fd);
      break;
    case NONE:
      break;
    }
    if (i == clients.size())
      break;
  }

  // CheckTimeOut();
}

void ClientManager::CheckTimeOut() {
  vector<Client> &clients = ClientManager::clients;

  for (vector<Client>::iterator it = clients.begin(); it != clients.end();
       it++) {
    if ((time(NULL) - it->data.lastActTime) > TIMEOUT) {
      OnDisConnect(it->data.fd);
      if (it == clients.end())
        break;
    }
  }
}