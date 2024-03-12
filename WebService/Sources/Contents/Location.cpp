#include "../../Headers/Contents/Http.hpp"
Location::Location() {

  members.domainPath = ".";
  members.rootPath = "";
  members.indexPath = "";
  members.isAutoIndex = false;
  members.methods[GET] = true;
  members.methods[POST] = true;
  members.methods[DELETE] = true;
}
Location::~Location() {}

const string Location::GetDomainPath() const { return members.domainPath; }
const string Location::GetIndexPath() const { return members.indexPath; }
const string Location::GetRedirectionPath() const { return members.returnPath; }
bool Location::GetIsAutoIndex() const { return members.isAutoIndex; }
const string Location::GetRootPath() const { return members.rootPath; }
bool Location::GetMethod(unsigned short i) const { return members.methods[i]; }
const string Location::GetCgiPath() const { return members.cgiPath; }

void Location::SetDomainPath(const string path) { members.domainPath = path; }
void Location::SetIndexPath(const string path) { members.indexPath = path; }
void Location::SetRedirectionPath(const string path) {
  members.returnPath = path;
}
void Location::SetCgiPath(const string path) { members.cgiPath = path; }
void Location::SetRootPath(const string path) { members.rootPath = path; }
void Location::SetIsAutoIndex(const bool f) { members.isAutoIndex = f; }
void Location::SetMethod(METHOD m, const bool f) { members.methods[m] = f; }
void Location::ClearMethod() {
  members.methods[GET] = false;
  members.methods[POST] = false;
  members.methods[DELETE] = false;
}
