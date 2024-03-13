#include "../../../Headers/Contents/Http.hpp"
#include "../../../Headers/Core/Client.hpp"

string Client::GetMsgHeaderValue(string key) {
  string value;
  string head = requestData.header;
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
  size_t methodLen = requestData.method.length() + 1;
  size_t posOfStartHttp = requestData.line.find("HTTP") - 1;

  try {
    root = requestData.line.substr(methodLen, posOfStartHttp - methodLen);
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }

  return root;
}

string Client::GetHttpVersion() {
  string ret;
  size_t posOfStart = requestData.line.find("HTTP/") + 5;
  size_t posOfNewLine = requestData.line.find("\r\n");

  try {
    ret = requestData.line.substr(posOfStart, posOfNewLine - posOfStart);
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }

  return ret;
}

void Client::SetBodyData(size_t firstEofPos) {
  string findStr = "Content-Length: ";
  size_t pos = requestData.header.find(findStr);

  try {
    if (pos == string::npos)
      return;
    pos += findStr.length();
    size_t newLinePos = requestData.header.find("\r\n");
    requestData.bodySize =
        StringToInt(requestData.header.substr(pos, newLinePos - pos));

    requestData.body =
        requestData.total.substr(firstEofPos + 4, requestData.bodySize);
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }
}

void Client::SetRequestData() {
  try {
    size_t posOfBlankline = requestData.total.find("\r\n\r\n");
    size_t posOfFirstNewLine = requestData.total.find("\r\n");
    data.reqCnt++;

    requestData.header = requestData.total.substr(0, posOfBlankline);
    requestData.line = requestData.header.substr(0, posOfFirstNewLine);
    SetBodyData(posOfBlankline);
    SetMethod();
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }
}

void Client::SetMethod() {
  string method = requestData.header.substr(0, 6);

  if (method.find("GET") != string::npos)
    requestData.method = "GET";
  else if (method.find("POST") != string::npos)
    requestData.method = "POST";
  else if (method.find("DELETE") != string::npos)
    requestData.method = "DELETE";
  else
    requestData.method = "ERROR";
}

void Client::SetData() {
  string totalAddr = GetMsgHeaderValue("Host");
  string cookie = GetMsgHeaderValue("Cookie");
  size_t addrColonPos = totalAddr.find(":");

  data.addr = totalAddr.substr(0, addrColonPos);
  if (!data.addr.compare("localhost"))
    data.addr = "127.0.0.1";
  requestData.root = GetRoot();
  data.httpVer = GetHttpVersion();
  data.port = StringToInt(totalAddr.substr(addrColonPos + 1));
  cookies.SetCookies(cookie);
}

void Client::CheckValidClient() {
  std::string root = requestData.root;
  int port = data.port;
  std::string method = requestData.method;

  Server server = http.GetServer(port);

  if (server.GetHost().compare(data.addr)) {
    responseStatus = 403;
    return;
  }

  Location location = server.GetLocation(root);
  if (location.GetDomainPath().compare(requestData.root)) {
    if (root.rfind(".js") == string::npos &&
        root.rfind(".css") == string::npos &&
        root.substr(0, 7).compare("/images")) {
      responseStatus = 404;
      return;
    }
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
  else if (port == 65536 || server.GetPort() != port)
    responseStatus = 421;
  else if (data.reqCnt >= MAX_REQUEST_CNT)
    responseStatus = 429;
}

map<string, string> Client::ParseQueryString() {
  map<string, string> ret;
  string body = requestData.body;
  size_t start = 0;
  size_t end = 0;

  try {
    while (true) {
      end = body.find("=", end);
      string key = body.substr(start, end - start);
      end++;
      start = end;
      end = body.find("&", end);
      if (end == string::npos) {
        ret[key] = body.substr(start);
        break;
      }
      ret[key] = body.substr(start, end - start);
    }
  } catch (exception &e) {
    cerr << e.what() << ", " << __FUNCTION__ << endl;
  }
  return ret;
}