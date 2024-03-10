#ifndef LOCATION_HPP
#define LOCATION_HPP
#include "../Utils/Define.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

class Server;

class Location {

private:
  LOCATION_MEMBER members;

public:
  Location();
  ~Location();
  const string GetDomainPath() const;
  const string GetIndexPath() const;
  const string GetReturnPath() const;
  const string GetCgiPath() const;
  const string GetRootPath() const;
  bool GetIsAutoIndex() const;
  bool GetMethod(unsigned short i) const;

  void SetDomainPath(const string path);
  void SetIndexPath(const string path);
  void SetReturnPath(const string path);
  void SetRootPath(const string path);
  void SetCgiPath(const string path);
  void SetIsAutoIndex(const bool f);
  void SetMethod(METHOD m, const bool f);
  void ClearMethod();
};

#endif