#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Utils/Define.hpp"
#include "Cookie.hpp"

class Client {
private:
  Cookie cookies;
  void SetData();
  void WriteGet();
  void SetMethod();
  void WritePost();
  void WriteDelete();
  void SetRequestData();
  void CheckValidClient();
  void UpdateResponseState();
  void WriteResponse(string msg, string content);

  string GetRoot();
  string BuildErrContent();
  string BuildContent();
  string BuildNormalContent();
  string GetHttpVersion();
  string BuildAutoindexContent();
  string BuildRedirecionContent();
  string GetMsg(int contentLen);
  string GetMsgHeaderValue(string key);
  string BuildAutoindex(string servRoot, string locRoot);

public:
  CLIENT_DATA data;
  Client();
  ~Client();
  void DataClear();
  void UpdateRead();
  void UpdateWrite();
  void UpdateError();
};

#endif