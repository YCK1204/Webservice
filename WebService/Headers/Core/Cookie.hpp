#ifndef COOKIEE_HPP
#define COOKIEE_HPP

#include <iostream>
#include <map>
#include <string>

using namespace std;
class Cookie {
private:
  map<string, string> cookies;
  void SetCookie(string key, string value);

public:
  void SetCookies(string cookies);
};

#endif