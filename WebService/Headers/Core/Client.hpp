#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Utils/Define.hpp"
#include "Cookie.hpp"

class Client {
private:
  Cookie cookies;
  void SetData();
  void HandleWrite();
  void SetMethod();
  void SetRequestData();
  void CheckValidClient();
  void UpdateResponseState();
  void SetBodyData(size_t firstEofPos);
  void WriteResponse(string msg, string content);
  
  string GetRoot();
  string HandlePost();
  string BuildContent();
  string GetHttpVersion();
  string BuildJsContent();
  string BuildErrContent();
  string BuildCssContent();
  string BuildImgContent();
  string BuildNormalContent();
  string GetMsg(int contentLen);
  string BuildAutoindexContent();
  string BuildRedirecionContent();
  string GetMsgHeaderValue(string key);
  string BuildFileContent(const string path);
  string BuildAutoindex(string servRoot, string locRoot);

  map<string, string> ParseQueryString();

public:
  CLIENT_DATA data;
  Request requestData;
  Client();
  ~Client();
  void DataClear();
  void UpdateRead();
  void UpdateWrite();
  void UpdateError();
};

#endif