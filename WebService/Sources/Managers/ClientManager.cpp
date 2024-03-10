#include "../../Headers/Manager/ClientManager.hpp"
#include <sys/socket.h>

void ClientManager::OnConnect(int fd) {
  CLIENT_DATA data;

  memset(&data, 0, sizeof(CLIENT_DATA));
  Client client;
  client.data = data;
  clients[fd] = client;
}

void ClientManager::OnDisConnect(int fd) { clients.erase(fd); }

void ClientManager::CheckEvent(int maxFd, fd_set errorEvent, fd_set readEvent,
                               fd_set writeEvent) {
  for (int i = 0; i <= maxFd; i++) {
    if (FD_ISSET(i, &errorEvent))
      clients[i].data.state = ERROR;
    else if (FD_ISSET(i, &readEvent))
      clients[i].data.state = READ;
    else if (FD_ISSET(i, &writeEvent))
      clients[i].data.state = WRITE;
  }
  // HandleErrEvent(i);
  // HandleReadEvent(i);
}