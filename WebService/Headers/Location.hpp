#ifndef LOCATION_HPP
#define LOCATION_HPP
#include "Define.hpp"
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
  string rootPath;
  string indexPath;
  string returnPath;
  bool isAutoIndex;
  bool methods[3];

public:
  ~Location();
  const string GetRootPath() const;
  const string GetIndexPath() const;
  const string GetReturnPath() const;
  bool GetIsAutoIndex() const;
  bool GetMethod(unsigned short i) const;

  void SetRootPath(const string path);
  void SetIndexPath(const string path);
  void SetReturnPath(const string path);
  void SetIsAutoIndex(const bool f);
  void SetMethod(METHOD m, const bool f);
};

#endif