#include "../../Headers/Contents/Http.hpp"

bool IsValidHost(string host) {
  size_t i = 0, start = 0;
  bool success = true;
  int cnt = 0;

  while (true) {
    string num;
    i = host.find(".", i);

    if (i == string::npos) {
      num = host.substr(start, i - start);
      int n = atoi(num.c_str());
      success &= (0 <= n && n <= 255);
      break;
    }
    num = host.substr(start, i - start);
    int n = atoi(num.c_str());
    success &= (0 <= n && n <= 255);
    cnt++;
    i++;
    start = i;
  }
  success &= (cnt == 3);
  return success;
}

void CheckValidLocation(Location loc) {
  string domainPath = loc.GetDomainPath();

  if (domainPath.find("--") != string::npos)
    IsNotValidLocation(
        domainPath,
        "If there are two or more consecutive hyphens, it is not allowed");
  if (domainPath.find(".") != string::npos)
    IsNotValidLocation(domainPath, "If dots are included, it is not allowed");
}

bool ParseServerMember(stringstream &ss, fstream &f, Server &serv) {
  string first, second;
  bool success = true;

  first = ExtractWithComments(ss);
  second = ExtractWithComments(ss);

  if (first[0] == '#') {
    return true;
  } else if (!first.compare("listen")) {
    serv.SetPort(atoi(second.c_str()));
    int port = serv.GetPort();
    success &= !(port <= 1023 || port > 65535);
  } else if (!first.compare("server_name")) {
    serv.SetName(second);
  } else if (!first.compare("root")) {
    serv.SetRootPath(second);
    success &= IsExistFolder(second);
  } else if (!first.compare("client_body_size")) {
    serv.SetSize(atoi(second.c_str()));
    long size = serv.GetSize();
    success &= (0 <= size && size <= serv.GetSize());
  } else if (!first.compare("index")) {
    serv.SetIndexPath(second);
  } else if (!first.compare("error_page")) {
    serv.SetErrorPath(second);
  } else if (!first.compare("host")) {
    serv.SetHost(second);
    success &= IsValidHost(second);
  } else if (!first.compare("js_path")) {
    serv.SetJsRootPath(second);
  } else if (!first.compare("css_path")) {
    serv.SetCssRootPath(second);
  } else if (!first.compare("img_path")) {
    serv.SetImgRootPath(second);
  } else if (!first.compare("location")) {
    Location location;
    location = ParseLocation(ss, f, serv, second);
    CheckValidLocation(location);
    
    serv.AddLocation(location);
  } else {
    return false;
  }
  success &= !IsRemaingString(ss);
  return success;
}

Server ParseServer(fstream &f) {
  Server ret;
  string line;
  bool success = true;

  while (!f.eof()) {
    numOfLine++;
    getline(f, line);
    line = trim(ExtractWithComments(line));

    if (line.empty())
      continue;

    if (!line.compare("}"))
      break;

    stringstream ss(line);

    success &= ParseServerMember(ss, f, ret);
    if (success == false)
      break;
  }

  {
    ret.SetJsRootPath(ret.GetRootPath() + ret.GetJsRootPath());
    ret.SetCssRootPath(ret.GetRootPath() + ret.GetCssRootPath());
    ret.SetImgRootPath(ret.GetRootPath() + ret.GetImgRootPath());
    success &= IsExistFile(ret.GetRootPath() + ret.GetIndexPath());
    success &= IsExistFile(ret.GetRootPath() + ret.GetErrorPath());
    success &= IsExistFolder(ret.GetJsRootPath());
    success &= IsExistFolder(ret.GetCssRootPath());
    success &= IsExistFolder(ret.GetImgRootPath());
  }

  if (success == false) {
    FT_THROW("Is Not vaild server member ( " + line +
                 " ), Line : " + IntToString(numOfLine),
             ERR_CONF);
  }
  return ret;
}