#include "../Headers/Core/Client.hpp"
#include "../Headers/Manager/Manager.hpp"
#include <cstring>
#include <sys/socket.h>

Client::Client() {
  memset(&data, 0, sizeof(CLIENT_DATA));
  data.img.buf = new char[1];
}

void Client::Read() {
  size_t len;
  size_t &str_len = data.str_len;
  char *tmp;
  char buf[BUFFER_SIZE + 1];

  int n = recv(data.fd, buf, BUFFER_SIZE, 0);
  if (n <= 0) {
    Manager::Client.OnDisConnect(data.fd);
    return;
  }

  buf[n] = 0;
  data.request += buf;
  tmp = new char[str_len + 1];
  for (size_t i = 0; i < str_len; i++) {
    tmp[i] = data.img.buf[i];
  }

  tmp[str_len] = '\0';
  delete[] data.img.buf;
  data.str_len += n;
  data.img.buf = new char[str_len + 1];

  for (size_t i = 0; i < str_len - n; i++)
    data.img.buf[i] = tmp[i];
  for (ssize_t i = 0; i < n; i++)
    data.img.buf[i + (str_len - n)] = buf[i];
  data.img.buf[str_len] = '\0';

  data.last_active_times = time(NULL);
  len = data.request.find("\r\n\r\n");
  delete[] tmp;
  if (len != string::npos) {
    data.state = WRITE;
    // if (!strncmp(client.data.request.c_str(), "POST", 4))
    //   postHandler(clnt_sock, len);
    // else
    //   writeResponse(clnt_sock);
  }
}