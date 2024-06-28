#include "../../../Headers/Core/Client.hpp"
#include "../../../Headers/Managers/Manager.hpp"
#include "../../../Headers/Utils/Util.hpp"

void Client::UpdateWrite() {
  SetRequestData();
  SetData();
  CheckValidClient();
  UpdateResponseState();

  switch (requestData.method[0]) {
  case 'G':
  case 'P':
  case 'D':
    HandleWrite();
    break;
  default:
    data.state = ERROR;
    return;
  }

  if (time(NULL) - data.lastActTime < REQUEST_INTERVAL)
    data.reqCnt = 0;
}

void Client::WriteResponse(string msg, string content) {
  if (write(data.fd, msg.c_str(), msg.length()) == -1) {
    return;
  }
  if (write(data.fd, content.c_str(), content.length()) == -1) {
    return;
  }

  data.state = READ;
  Manager::Client.OnWrite(sizeof(msg) + sizeof(content), data.fd);
  
  DataClear();
}

void Client::HandleWrite() {
  string msg, content;

  content = BuildContent();
  msg = GetMsg(content.length());

  WriteResponse(msg, content);
}
