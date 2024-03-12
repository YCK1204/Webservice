#include "../../../Headers/Core/Client.hpp"
#include "../../../Headers/Managers/Manager.hpp"
#include "../../../Headers/Utils/Util.hpp"

void Client::UpdateWrite() {
  SetRequestData();
  SetData();
  CheckValidClient();
  UpdateResponseState();

  switch (data.request.total[0]) {
  case 'G':
    WriteGet();
    break;
  case 'P':
    WritePost();
    break;
  case 'D':
    WriteDelete();
    break;
  default:
    data.state = ERROR;
    return;
  }

  if (time(NULL) - data.lastActTime < REQUEST_INTERVAL)
    data.reqCnt = 0;
  data.state = ERROR;
}

void Client::WriteResponse(string msg, string content) {
  if (write(data.fd, msg.c_str(), msg.length()) == -1) {
    // cerr << ORANGE "Error : write error (response msg)" CLEAR << endl;
    data.state = ERROR;
    return;
  }
  if (write(data.fd, content.c_str(), content.length()) == -1) {
    // cerr << ORANGE "Error : write error (response content)" CLEAR << endl;
    data.state = ERROR;
    return;
  }

  DataClear();

  // {
  //   // printLog(data.fd);
  //   if (responseStatus < 400) {
  //     checkSession(data.fd);
  //     decideConnecting(data.fd);
  //   } else {
  //     Manager::Client.OnDisConnect(data.fd);
  //   }
  // }
}

void Client::WriteGet() {
  string msg, content;

  responseStatus = 200;
  content = BuildContent();
  msg = GetMsg(content.length());

  WriteResponse(msg, content);
}

void Client::WritePost() {

  // size_t eofRequestHeadPos = data.request.find("\r\n\r\n");
  // size_t contentLenPos = data.request.find("Content-Length:");
  // int fd = data.fd;

  // if (contentLenPos == string::npos) {
  //   responseStatus = 400;
  //   WriteResponse();
  //   Manager::Client.OnDisConnect(fd);
  //   return;
  // }

  // data.bodySize = data.requestSize - (eofRequestHeadPos + 4);

  // if (data.bodySize == StringToInt(data.request.substr(contentLenPos + 16)))
  // {
  //   data.body = data.request.substr(eofRequestHeadPos + 4);
  //   data.body_method = getBodyMethod(fd);
  //   if (data.body.find("------WebKitFormBoundary") == string::npos) {
  //     data.body = decoding(data.body);
  //   } else {
  //     parsingFormData(fd);
  //   }
  //   writeResponse( , );
  // } else {
  //   data.body.clear();
  // }
}

void Client::WriteDelete() {}
