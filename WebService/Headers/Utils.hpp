#ifndef UTILS_HPP
#define UTILS_HPP

#include "Server.hpp"
#include <dirent.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
Server ParseServer(fstream &f);
string trim(const string &s);
string StringToLower(string str);
Location ParseLocation(stringstream &ss, fstream &f);
bool IsRemaingString(stringstream &ss);
string IntToString(int n);
bool IsExistFolder(string path);
bool IsExistFile(string path);
#endif