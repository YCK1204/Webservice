#include "../../Headers/Http.hpp"
Location::~Location() {}

const string Location::GetRootPath() const { return rootPath; }
const string Location::GetIndexPath() const { return indexPath; }
const string Location::GetReturnPath() const { return returnPath; }
bool Location::GetIsAutoIndex() const { return isAutoIndex; }
bool Location::GetMethod(unsigned short i) const { return methods[i]; }

void Location::SetRootPath(const string path) { rootPath = path; }
void Location::SetIndexPath(const string path) { indexPath = path; }
void Location::SetReturnPath(const string path) { returnPath = path; }
void Location::SetIsAutoIndex(const bool f) { isAutoIndex = f; }
void Location::SetMethod(METHOD m, const bool f) { methods[m] = f; }