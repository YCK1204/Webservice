#include "../../Headers/Utils/Util.hpp"
#include "../../Headers/Utils/Exception.hpp"
#include <iomanip>
const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string &s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) { return rtrim(ltrim(s)); }

string StringToLower(string str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (str[i] >= 65 && str[i] <= 90)
      str[i] += 32;
  }

  return str;
}

bool IsRemaingString(stringstream &ss) {
  string str;
  ss >> str;

  if (str[0] == '#')
    return false;
  if (!str.compare("{")) {
    str.clear();
    ss >> str;
  }
  return !str.empty();
}

string IntToString(int n) {
  string ret;
  int len = 1;
  int tmp = n;

  while ((tmp /= 10))
    len++;

  for (int i = len - 1; i >= 0; i--) {
    string a;
    a += n % 10 + '0';
    ret.insert(0, a);
    n /= 10;
  }
  return ret;
}

int StringToInt(string str) { return atoi(str.c_str()); }

bool IsExistFolder(string path) {
  DIR *dir;

  dir = opendir(path.c_str());
  if (dir != NULL) {
    closedir(dir);
    return true;
  }
  return false;
}

bool IsExistFile(string path) {
  ifstream file(path);

  if (IsExistFolder(path))
    return false;
  if (file.is_open()) {
    file.close();
    return true;
  }
  return false;
}

string ExtractWithComments(stringstream &ss) {
  string ret;

  ss >> ret;

  size_t i = ret.find('#');
  if (i != string::npos)
    ret = ret.substr(0, i);
  return ret;
}

string ExtractWithComments(string str) {
  size_t i = str.find('#');
  if (i != string::npos)
    str = str.substr(0, i);
  return str;
}

void CheckValidServer(const Server &serv) {
  if (serv.GetPort() == 0)
    IsNotValidServer(serv.GetPort(), "Port has to be set");
  if (serv.GetRootPath().empty())
    IsNotValidServer(serv.GetPort(), "Root path has to be set");
  if (serv.GetIndexPath().empty())
    IsNotValidServer(serv.GetPort(), "Index path has to be set");
  if (serv.GetHost().empty())
    IsNotValidServer(serv.GetPort(), "Host address has to be set");
  if (!serv.GetRootPath().compare(".") || !serv.GetRootPath().compare("./"))
    IsNotValidServer(serv.GetPort(),
                     "Root path should be located within a subdirectory");
}

string GetDate() {
  int month;
  char buffer[80];
  ssize_t monthPos;
  struct tm *selTimeInfo;
  time_t rawTime, selTime;
  string dateHeader, monthName;
  const char *monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                              "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  time(&rawTime);
  selTime = rawTime + (9 * 3600);
  selTimeInfo = gmtime(&selTime);
  strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S SEL", selTimeInfo);
  dateHeader = static_cast<string>(buffer);
  month = selTimeInfo->tm_mon;
  monthName = monthNames[month];
  monthPos = dateHeader.find("MMM");
  if (static_cast<size_t>(monthPos) != string::npos)
    dateHeader.replace(monthPos, 3, monthName);
  return dateHeader;
}

string ReadFile(string file_path) {
  string total, line;
  ifstream file;

  file.open(file_path.c_str());

  while (getline(file, line)) {
    total += line;
    line.clear();
    if (!file.eof())
      total += '\n';
  }

  file.close();
  return total;
}

// void printLog(int clnt_sock) {
//   // if (responseStatus) {
//   //   cout << RED << "Response to client : " << clnt_sock << ",
//   status=["
//   //             << err << "], method=[" << clients[clnt_sock].method
//   //             << "], URI=" << clients[clnt_sock].root << CLEAR <<
//   endl;
//   // } else {
//   //   const char *const color = status >= 300   ? LIME
//   //                             : status <= 200 ? SKY_BLUE
//   //                                             : YELLOW;
//   //   cout << color << "Response to client : " << clnt_sock << ",
//   status=["
//   //             << status << "], method=[" << clients[clnt_sock].method
//   //             << "], URI=" << clients[clnt_sock].root << CLEAR <<
//   endl;
//   // }
// }