#include "../../Headers/Core/Cookie.hpp"

void Cookie::SetCookie(string key, string value) { cookies[key] = value; }

void Cookie::SetCookies(string cookies) {
  string key, value;

  if (cookies.length() > 0) {
    try {
      size_t end = 0;
      size_t start = 0;
      size_t semiColonPos = 0;
      while (true) {
        semiColonPos = cookies.find(";");
        if (semiColonPos == string::npos)
          break;

        end = cookies.find("=");
        key = cookies.substr(start, end - start);
        value = cookies.substr(end + 1, semiColonPos);
        SetCookie(key, value);
        start = semiColonPos + 1;
      }

      end = cookies.find("=");
      key = cookies.substr(start, end - start);
      value = cookies.substr(end + 1, semiColonPos);
      SetCookie(key, value);

    } catch (exception &e) {
      cerr << e.what() << ", " << __FUNCTION__ << endl;
    }
  }
}