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
}

void Client::WriteResponse(string msg, string content) {
  if (write(data.fd, msg.c_str(), msg.length()) == -1) {
    // cerr << ORANGE "Error : write error (response msg)" CLEAR << endl;
    return;
  }
  if (write(data.fd, content.c_str(), content.length()) == -1) {
    // cerr << ORANGE "Error : write error (response content)" CLEAR << endl;
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

  content = BuildContent();
  msg = GetMsg(content.length());

  WriteResponse(msg, content);
}

void Client::WritePost() {
  map<string, string> postData = ParseQueryString();
  if (postData.find("method") == postData.end())
    return;
  // board
  // file upload

  // sign_in
  // sign_up
  // sign_out

}

void Client::WriteDelete() {}
