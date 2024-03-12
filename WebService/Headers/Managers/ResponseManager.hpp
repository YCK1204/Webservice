#ifndef RESPONSEMANAGER_HPP
#define RESPONSEMANAGER_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class ResponseManager {
private:
public:
  static map<string, string> type;
  static map<int, string> status;
  static string GetStatus(const int &n);
  static string GetType(const string &type);
  static void Init();
};

#endif
