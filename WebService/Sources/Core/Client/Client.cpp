#include "../../../Headers/Contents/Http.hpp"

Client::Client() {
  DataClear();
  data.reqCnt = 0;
}

void Client::DataClear() {
  responseStatus = 200;

  {
    data.addr.clear();
    data.httpVer.clear();
    data.fileExtension = "html";
    data.lastActTime = time(NULL);
  }

  {
    data.cal.result.clear();
    data.cal.display.clear();
  }

  {
    requestData.body.clear();
    requestData.line.clear();
    requestData.root.clear();
    requestData.total.clear();
    requestData.header.clear();
    requestData.method.clear();
  }
}

void Client::UpdateResponseState() {
  if (responseStatus >= 400) {
    data.responseState = ERR;
    return;
  }

  Server server = http.GetServer(data.port);
  Location location = server.GetLocation(requestData.root);
  if (!location.GetRedirectionPath().empty())
    data.responseState = REDIRECTION;
  else if (location.GetIsAutoIndex())
    data.responseState = AUTOINDEX;
  else if (requestData.root.rfind(".js") != string::npos)
    data.responseState = JS;
  else if (requestData.root.rfind(".css") != string::npos)
    data.responseState = CSS;
  else if (requestData.root.find("/images") != string::npos)
    data.responseState = IMG;
  else
    data.responseState = NORMAL;
}

Client::~Client() { DataClear(); }
