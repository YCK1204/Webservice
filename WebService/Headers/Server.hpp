#ifndef SERVER_HPP
#define SERVER_HPP

#include "Location.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

class Location;

class Server {

private:
  int port;
  long clientBodySize;
  string serverName;
  string defaultIndexPath;
  string errorPagePath;
  string host;
  string rootPath;
  vector<Location> locations;

public:
  Server();
  ~Server();
  int GetPort() const;
  long GetSize() const;
  const string GetName() const;
  const string GetIndexPath() const;
  const string GetErrorPath() const;
  const string GetHost() const;
  const string GetRootPath() const;
  const Location GetLocation(const string path);
  vector<Location> GetLocation();

  void SetPort(const int port);
  void SetSize(const long size);
  void SetName(const string name);
  void SetIndexPath(const string path);
  void SetErrorPath(const string path);
  void SetHost(const string host);
  void SetRootPath(const string path);
  void AddLocation(Location &location);
};

#endif