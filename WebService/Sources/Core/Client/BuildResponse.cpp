#include "../../../Headers/Contents/Http.hpp"
#include <algorithm>
#include <sys/stat.h>
/* #region Build Contents */
/* #region Build Autoindex Content */

bool CompareFiles(const FileStream &f1, const FileStream &f2) {
  return f1.name < f2.name;
}

string FormatSize(double size) {
  const char *units[] = {"B", "KB", "MB", "GB", "TB"};
  int unitIndex = 0;
  while (size >= 1024 && unitIndex < 4) {
    size /= 1024;
    unitIndex++;
  }

  ostringstream oss;
  oss << fixed << setprecision(2) << size << " " << units[unitIndex];
  return oss.str();
}

string FormatTime(const time_t &time) {
  struct tm *timeinfo;
  char buffer[80];
  timeinfo = localtime(&time);
  strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", timeinfo);
  return string(buffer);
}

string Client::BuildAutoindexContent() {
  Server server = http.GetServer(data.port);
  string autoindex = BuildAutoindex(server.GetRootPath(), requestData.root);

  if (responseStatus >= 400) {
    data.responseState = ERR;
    return BuildErrContent();
  }
  return autoindex;
}

string Client::BuildAutoindex(string servRoot, string locRoot) {
  string ret, msg, dirRoot;
  DIR *dir;
  struct dirent *entry;
  struct stat fileStat;
  vector<FileStream> files;

  dirRoot = servRoot;
  if (locRoot[0] == '/')
    locRoot = locRoot.substr(1);
  dirRoot += locRoot;
  dir = opendir(dirRoot.c_str());
  if (dir) {
    while ((entry = readdir(dir)) != NULL) {
      string file_path = dirRoot + "/" + entry->d_name;
      FileStream file;
      file.name = static_cast<string>(entry->d_name);
      file.lastModified = fileStat.st_mtime;
      file.size = fileStat.st_size;
      if (S_ISDIR(fileStat.st_mode))
        file.is_dir = true;
      else
        file.is_dir = false;
      files.push_back(file);
    }
    sort(files.begin(), files.end(), CompareFiles);
    msg += "    <table>\n<tr><th>Name</th><th>Last "
           "Modified</th><th>Size</th></tr>\n";
    for (vector<FileStream>::iterator it = files.begin(); it != files.end();
         it++) {
      msg += "    <tr>";
      if (it->is_dir)
        msg += "        <td><a href=\"" + it->name + "/\">" + it->name +
               "/</a></td>\n";
      else
        msg += "        <td><a href=\"" + it->name + "\">" + it->name +
               "</a></td>\n";
      msg += "        <td>" + FormatTime(it->lastModified) + "</td>\n";
      double fileSize = static_cast<double>(it->size);
      msg += "        <td>" + FormatSize(fileSize) + "</td>\n";
      msg += "    </tr>\n";
    }
    msg += "    </table>\n";
    ret = http.html.Format(http.html.GetString(), "", msg.c_str());
  } else {
    responseStatus = 500;
    return "";
  }
  return ret;
}
/* #endregion */
/* #region Build Error Content */
string Client::BuildErrContent() {
  if (!requestData.root.compare("/favicon.ico")) {
    return "";
  }

  if (responseStatus == 404) {
    Server serv = http.GetServer(data.port);
    return ReadFile(serv.GetRootPath() + serv.GetErrorPath());
  }

  string code = Manager::Response.GetStatus(responseStatus);

  StringFormat body;
  body = "{1}\
</h1>\
<p> {2} </p>";

  return body.Format(body.GetString(), IntToString(responseStatus).c_str(),
                     code.c_str());
}
/* #endregion */
/* #region Build Redirecion Content */
string Client::BuildRedirecionContent() { return ""; }
/* #endregion */
/* #region Build Normal Content */
string Client::BuildNormalContent() {
  Server server = http.GetServer(data.port);
  Location location = server.GetLocation(requestData.root);
  string root = location.GetRootPath() + location.GetIndexPath();

  return ReadFile(root);
}
/* #endregion */
string Client::BuildFileContent(const string path) {
  size_t slashPos = requestData.root.rfind("/");
  string fileName = requestData.root.substr(slashPos);
  data.fileExtension = fileName.substr(fileName.rfind(".") + 1);

  string root = path + fileName;
  return ReadFile(root);
}

string Client::BuildJsContent() {
  Server server = http.GetServer(data.port);
  return BuildFileContent(server.GetJsRootPath());
}

string Client::BuildCssContent() {
  Server server = http.GetServer(data.port);
  return BuildFileContent(server.GetCssRootPath());
}

string Client::BuildImgContent() {
  Server server = http.GetServer(data.port);
  return BuildFileContent(server.GetImgRootPath());
}

/* #endregion */
string Client::BuildContent() {

  switch (data.responseState) {
  case ERR:
    return BuildErrContent();
  case REDIRECTION:
    return BuildRedirecionContent();
  case AUTOINDEX:
    return BuildAutoindexContent();
  case NORMAL:
    return BuildNormalContent();
  case JS:
    return BuildJsContent();
  case CSS:
    return BuildCssContent();
  case IMG:
    return BuildImgContent();
  }

  return "";
}

string Client::GetMsg(int contentLen) {
  Server server = http.GetServer(data.port);
  Location location = server.GetLocation(requestData.root);

  struct stat fileStat;

  string filePath = location.GetRootPath() + location.GetIndexPath();
  stat(filePath.c_str(), &fileStat);

  string msg = http.responseMsgHeaders.Format(
      http.responseMsgHeaders.GetString(), IntToString(responseStatus).c_str(),
      Manager::Response.GetStatus(responseStatus).c_str(),
      IntToString(contentLen).c_str(),
      Manager::Response.type[data.fileExtension].c_str(), GetDate().c_str(),
      IntToString(TIMEOUT).c_str(), IntToString(MAX_REQUEST_CNT).c_str(),
      FormatTime(fileStat.st_mtime).c_str());

  if (!location.GetRedirectionPath().empty())
    msg += "Location: " + location.GetRedirectionPath() + "\r\n";

  if (!server.GetName().empty())
    msg += "Server: " + server.GetName() + "\r\n";

  msg += "\r\n";

  return msg;
  // if (clients[clnt_sock].set_cookie)
  //   ss << createCookie(clnt_sock);
  // else if (clients[clnt_sock].delete_cookie)
  //   ss << deleteCookie();
}