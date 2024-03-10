#ifndef UTILS_HPP
#define UTILS_HPP

#include "../Contents/Server.hpp"
#include <arpa/inet.h>
#include <dirent.h>
#include <exception>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sstream>
#include <string>
#include <sys/_endian.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
using namespace std;

Server ParseServer(fstream &f);
string trim(const string &s);
string StringToLower(string str);
Location ParseLocation(stringstream &ss, fstream &f, string root,
                       string domainRoot);
bool IsRemaingString(stringstream &ss);
string IntToString(int n);
bool IsExistFolder(string path);
bool IsExistFile(string path);
string ExtractWithComments(stringstream &ss);
string ExtractWithComments(string str);
void CheckValidServer(const Server &serv);
#endif