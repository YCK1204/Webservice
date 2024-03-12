#include "../../../Headers/Contents/Http.hpp"
#include "../../../Headers/Core/Client.hpp"

string Client::GetMsgHeaderValue(string key) {
  string value;
  string head = data.request.header;
  size_t pos = head.find(key);

  if (pos != string::npos) {
    try {
      size_t posOfNewLine = head.find("\r\n", pos);
      ushort keyLen = key.length() + 2;
      value = head.substr(pos + keyLen, posOfNewLine - (pos + keyLen));
    } catch (exception &e) {
      cerr << e.what() << ", " << __FUNCTION__ << endl;
    }
  }

  return value;
}

string Client::GetRoot() {
  string root;
  size_t methodLen = data.request.method.length() + 1;
  size_t posOfStartHttp = data.request.line.find("HTTP") - 1;

  try {
    root = data.request.line.substr(methodLen, posOfStartHttp - methodLen);
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }

  return root;
}

string Client::GetHttpVersion() {
  string ret;
  size_t posOfStart = data.request.line.find("HTTP/") + 5;
  size_t posOfNewLine = data.request.line.find("\r\n");

  try {
    ret = data.request.line.substr(posOfStart, posOfNewLine - posOfStart);
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }

  return ret;
}

void Client::SetRequestData() {
  try {
    size_t posOfBlankline = data.request.total.find("\r\n\r\n");
    size_t posOfFirstNewLine = data.request.total.find("\r\n");
    data.reqCnt++;

    data.request.header = data.request.total.substr(0, posOfBlankline);
    data.request.body = data.request.total.substr(posOfBlankline);
    data.request.line = data.request.header.substr(0, posOfFirstNewLine);
    SetMethod();
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }
}

void Client::SetMethod() {
  string method = data.request.header.substr(0, 6);

  if (method.find("GET") != string::npos)
    data.request.method = "GET";
  else if (method.find("POST") != string::npos)
    data.request.method = "POST";
  else if (method.find("DELETE") != string::npos)
    data.request.method = "DELETE";
  else
    data.request.method = "ERROR";
}

void Client::SetData() {
  string totalAddr = GetMsgHeaderValue("Host");
  string cookie = GetMsgHeaderValue("Cookie");
  size_t addrColonPos = totalAddr.find(":");

  data.addr = totalAddr.substr(0, addrColonPos);
  if (!data.addr.compare("localhost"))
    data.addr = "127.0.0.1";
  data.request.root = GetRoot();
  data.httpVer = GetHttpVersion();
  data.port = StringToInt(totalAddr.substr(addrColonPos + 1));
  cookies.SetCookies(cookie);
}

void Client::CheckValidClient() {
  std::string root = data.request.root;
  int port = data.port;
  std::string method = data.request.method;

  Server server = http.GetServer(port);

  if (server.GetHost().compare(data.addr)) {
    responseStatus = 403;
    return;
  }

  Location location = server.GetLocation(root);
  if (location.GetDomainPath().compare(data.request.root)) {
    responseStatus = 404;
    return;
  }

  bool methods[3] = {location.GetMethod(0), location.GetMethod(1),
                     location.GetMethod(2)};

  if (((!methods[GET] && !method.compare("GET")) ||
       (!methods[POST] && !method.compare("POST")) ||
       (!methods[DELETE] && !method.compare("DELETE")))) {
    responseStatus = 405;
    return;
  }

  if (root.length() > MAX_ROOT_LEN)
    responseStatus = 414;
  else if (data.httpVer.compare("1.1"))
    responseStatus = 505;
  else if (server.GetHost().compare(data.addr))
    responseStatus = 403;
  else if (port == 65536 || server.GetPort() != port)
    responseStatus = 421;
  else if (data.reqCnt >= MAX_REQUEST_CNT)
    responseStatus = 429;
}