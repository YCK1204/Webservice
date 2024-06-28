#include "../../../Headers/Core/Client.hpp"
#include "../../../Headers/Managers/Manager.hpp"
#include "../../../Headers/Utils/Util.hpp"

void Client::UpdateRead() {
  char buf[BUFFER_SIZE + 1];

  int n = recv(data.fd, buf, BUFFER_SIZE, 0);
  if (n <= 0) {
    data.state = ERROR;
    return;
  }

  {
    buf[n] = 0;
    for (int i = 0; i < n; i++)
      requestData.total += buf[i];
    data.lastActTime = time(NULL);
  }
  
  {
    size_t blankLinePos = requestData.total.find("\r\n\r\n");
    if (blankLinePos != string::npos) {
      if (requestData.total.find("content-length") != string::npos) {
        if (requestData.total.find("\r\n\r\n",
                                   blankLinePos + 1 != string::npos)) {
          data.state = WRITE;
        }
      } else {
        data.state = WRITE;
      }
    }
  }

  if (requestData.total.size() >= MAX_CLIENT_REQUEST_SIZE)
    Manager::Client.OnDisConnect(data.fd);
}