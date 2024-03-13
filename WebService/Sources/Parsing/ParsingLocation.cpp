#include "../../Headers/Contents/Http.hpp"

bool SetAllowMethods(stringstream &ss, Location &loc, string method) {
  loc.ClearMethod();

  while (true) {
    if (method.empty())
      break;
    if (!method.compare("GET")) {
      loc.SetMethod(GET, true);
    } else if (!method.compare("POST")) {
      loc.SetMethod(POST, true);
    } else if (!method.compare("DELETE")) {
      loc.SetMethod(DELETE, true);
    } else {
      return false;
    }
    method.clear();
    method = ExtractWithComments(ss);
  }
  return true;
}

bool ParseLocationMember(stringstream &ss, Location &loc, string root) {
  string first, second;
  bool success = true;

  first = ExtractWithComments(ss);
  second = ExtractWithComments(ss);

  if (!first.compare("allow_methods")) {
    success &= SetAllowMethods(ss, loc, second);
  } else if (!first.compare("autoindex")) {
    success &= (!second.compare("on") || !second.compare("off"));
    loc.SetIsAutoIndex(!second.compare("on") ? true : false);
    if (!second.compare("on"))
      success &= IsExistFolder(root + loc.GetDomainPath());
  } else if (!first.compare("index")) {
    loc.SetIndexPath(second);
    success &= IsExistFile(root + loc.GetRootPath() + loc.GetIndexPath());
  } else if (!first.compare("return")) {
    loc.SetRedirectionPath(second);
  } else if (!first.compare("cgi-path")) {
    loc.SetCgiPath(root + second);
  } else if (!first.compare("root")) {
    loc.SetRootPath(second);
  } else {
    return false;
  }
  success &= !IsRemaingString(ss);
  return success;
}

Location ParseLocation(stringstream &ss, fstream &f, Server serv,
                       string domainRoot) {
  Location ret;
  bool success = true;
  string line;

  ret.SetDomainPath(domainRoot);
  if (IsRemaingString(ss))
    return ret;

  while (!f.eof()) {
    numOfLine++;
    getline(f, line);
    line = trim(ExtractWithComments(line));

    if (line.empty())
      continue;

    if (!line.compare("}"))
      break;

    stringstream s(line);
    success &= ParseLocationMember(s, ret, serv.GetRootPath());
    if (success == false)
      break;
  }

  {
    if (ret.GetIndexPath().empty())
      ret.SetIndexPath(serv.GetIndexPath());
    ret.SetRootPath(serv.GetRootPath() + ret.GetRootPath());

    if (!ret.GetCgiPath().empty())
      success &= IsExistFile(ret.GetRootPath() + ret.GetCgiPath());
    success &= IsExistFolder(ret.GetRootPath());
    success &= IsExistFile(ret.GetRootPath() + ret.GetIndexPath());
  }

  if (success == false)
    FT_THROW("Is Not vaild location member (" + line +
                 "), Line : " + IntToString(numOfLine),
             ERR_CONF);
  return ret;
}