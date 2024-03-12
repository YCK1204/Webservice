#include "../../../Headers/Core/Client.hpp"
#include "../../../Headers/Managers/Manager.hpp"
#include "../../../Headers/Utils/Util.hpp"

void Client::UpdateRead() {
  // size_t &reqSize = data.requestSize;
  // char *tmp;
  char buf[BUFFER_SIZE + 1];

  int n = recv(data.fd, buf, BUFFER_SIZE, 0);
  if (n <= 0) {
    data.state = ERROR;
    return;
  }

  {
    buf[n] = 0;
    data.request.total += buf;
    // tmp = new char[reqSize + 1];
    // for (size_t i = 0; i < reqSize; i++)
    //   tmp[i] = data.img.buf[i];
    // tmp[reqSize] = '\0';
    // if (data.img.buf)
    //   delete[] data.img.buf;
    data.requestSize += n;
    // data.img.buf = new char[reqSize + 1];
  }
  {
    // for (size_t i = 0; i < reqSize - n; i++)
    //   data.img.buf[i] = tmp[i];
    // for (ssize_t i = 0; i < n; i++)
    //   data.img.buf[i + (reqSize - n)] = buf[i];
    // data.img.buf[reqSize] = '\0';
    // cout << "readDelete tmp\n";
    // delete[] tmp;
    data.lastActTime = time(NULL);
  }

  size_t blankLinePos = data.request.total.find("\r\n\r\n");
  if (blankLinePos != string::npos) {
    if (data.request.total.find("content-length") != string::npos) {
      if (data.request.total.find("\r\n\r\n", blankLinePos + 1 != string::npos))
        data.state = WRITE;
    } else {
      data.state = WRITE;
    }
  }
}