#include "../../Headers/Http.hpp"

bool IsValidHost(string host) {
  size_t i = 0;
  bool success = true;
  int cnt = 0;

  while (true) {
    string num;
    i = host.find(".");

    if (i == string::npos) {
      num = host.substr(i, host.length() - i);
      int n = atoi(num.c_str());
      success &= (0 <= n && n <= 255);
      break;
    }
    num = host.substr(i, host.length() - i);
    int n = atoi(num.c_str());
    success &= (0 <= n && n <= 255);
    cnt++;
  }
  success &= (cnt == 3);
  return success;
}

void ParseServerMember(stringstream &ss, fstream &f, Server &serv) {
  string first, second;
  bool success = true;

  ss >> first;
  ss >> second;

  if (first[0] == '#') {
    return;
  } else if (!first.compare("server")) {
    success &= second.compare("{");
  } else if (!first.compare("listen")) {
    serv.SetPort(atoi(second.c_str()));
    int port = serv.GetPort();
    success &= !(port < 0 || port > 65535);
  } else if (!first.compare("server_name")) {
    serv.SetName(second);
  } else if (!first.compare("root")) {
    serv.SetRootPath(second);
    success &= IsExistFolder(second);
  } else if (!first.compare("client_body_size")) {
    serv.SetSize(atoi(second.c_str()));
    long size = serv.GetSize();
    success &= (0 <= size && size <= MAX_CLIENT_BODY_SIZE);
  } else if (!first.compare("index")) {
    serv.SetIndexPath(second);
    success &= IsExistFile(serv.GetRootPath() + serv.GetIndexPath());
  } else if (!first.compare("error_page")) {
    serv.SetErrorPath(second);
    success &= IsExistFile(serv.GetRootPath() + serv.GetErrorPath());
  } else if (!first.compare("host")) {
    serv.SetHost(second);
    success &= IsValidHost(second);
  } else if (!first.compare("location")) {
  } else {
    FT_THROW("Is Not vaild server member (" + first +
                 "), Line : " + IntToString(numOfLine),
             ERR_CONF);
  }
  success &= !IsRemaingString(ss);
}

Server ParseServer(fstream &f) {
  Server ret;
  string line;

  while (!f.eof()) {
    getline(f, line);
    line = StringToLower(trim(line));

    stringstream ss(line);
    ParseServerMember(ss, f, ret);
    numOfLine++;
  }
  return ret;
}