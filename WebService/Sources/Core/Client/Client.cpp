#include "../../../Headers/Contents/Http.hpp"

Client::Client() {
  data.img.buf = NULL;
  data.img.binary_request = NULL;
  DataClear();
}

void Client::DataClear() {
  {
    data.addr.clear();
    data.http.clear();
    data.state = READ;
    data.httpVer.clear();
    data.requestSize = 0;
    data.redirect.clear();
    data.fileExtension = "html";
    data.lastActTime = time(NULL);
  }

  {
    data.cal.result.clear();
    data.cal.display.clear();
  }

  {
    data.request.body.clear();
    data.request.line.clear();
    data.request.root.clear();
    data.request.total.clear();
    data.request.header.clear();
    data.request.method.clear();
  }

  {
    // if (data.img.buf != NULL) {
    //   cout << data.img.buf << endl;
    //   delete[] data.img.buf;
    // }
    // if (data.img.binary_request != NULL) {
    //   cout << "clear request\n";
    //   delete[] data.img.binary_request;
    //   data.img.binary_request = NULL;
    // }
    // data.img.buf = new char[2];
  }
}

void Client::UpdateResponseState() {
  if (responseStatus >= 400) {
    data.responseState = ERR;
    return;
  }

  Server server = http.GetServer(data.port);
  Location location = server.GetLocation(data.request.root);
  if (!location.GetRedirectionPath().empty())
    data.responseState = REDIRECTION;
  else if (location.GetIsAutoIndex())
    data.responseState = AUTOINDEX;
  else
    data.responseState = NORMAL;
}

Client::~Client() { DataClear(); }
