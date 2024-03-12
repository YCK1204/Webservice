#include "../../Headers/Managers/ResponseManager.hpp"

string ResponseManager::GetStatus(const int &n) {
  map<int, string>::iterator it = ResponseManager::status.find(n);
  if (it == ResponseManager::status.end())
    it = ResponseManager::status.find(404);
  return (it->second);
}

string ResponseManager::GetType(const string &type) {
  map<string, string>::iterator it = ResponseManager::type.find(type);
  if (it == ResponseManager::type.end())
    return "application/octet-stream";
  return (ResponseManager::type.find(type)->second);
}

void ResponseManager::Init() {
  ResponseManager::status[100] = "Continue";
  ResponseManager::status[101] = "Switching Protocols";
  ResponseManager::status[102] = "Processing";
  ResponseManager::status[103] = "Early Hints";

  /* success */
  ResponseManager::status[200] = "OK";
  ResponseManager::status[201] = "Created";
  ResponseManager::status[202] = "Accepted";
  ResponseManager::status[203] = "Non-Authoritative Information";
  ResponseManager::status[204] = "No Content";
  ResponseManager::status[205] = "Reset Content";
  ResponseManager::status[206] = "Partial Content";
  ResponseManager::status[207] = "Multi-Status";
  ResponseManager::status[208] = "Already Reported";
  ResponseManager::status[226] = "IM Used";

  /* redirection */
  ResponseManager::status[300] = "Multiple Choices";
  ResponseManager::status[301] = "Moved Permanently";
  ResponseManager::status[302] = "Found"; // MOVED_TEMPORARILY
  ResponseManager::status[303] = "See Other";
  ResponseManager::status[304] = "Not Modified";
  ResponseManager::status[305] = "Use Proxy";
  ResponseManager::status[307] = "Temporary Redirect";
  ResponseManager::status[308] = "Permanent Redirect";

  /* client error */
  ResponseManager::status[400] = "Bad Request";
  ResponseManager::status[401] = "Unauthorized";
  ResponseManager::status[402] = "Payment Required";
  ResponseManager::status[403] = "Forbidden";
  ResponseManager::status[404] = "Not Found";
  ResponseManager::status[405] = "Method Not Allowed";
  ResponseManager::status[406] = "Not Acceptable";
  ResponseManager::status[407] = "Proxy Authentication Required";
  ResponseManager::status[408] = "Request Timeout";
  ResponseManager::status[409] = "Conflict";
  ResponseManager::status[410] = "Gone";
  ResponseManager::status[411] = "Length Required";
  ResponseManager::status[412] = "Precondition Failed";
  ResponseManager::status[413] = "Request Entity Too Large";
  ResponseManager::status[414] = "Request-URI Too Long";
  ResponseManager::status[415] = "Unsupported Media Type";
  ResponseManager::status[416] = "Requested Range Not Satisfiable";
  ResponseManager::status[417] = "Expectation Failed";
  ResponseManager::status[426] = "Upgrade Required";
  ResponseManager::status[431] = "Request Header Fields Too Large";

  /* server errors */
  ResponseManager::status[500] = "Internal Server Error";
  ResponseManager::status[501] = "Not Implemented";
  ResponseManager::status[502] = "Bad Gateway";
  ResponseManager::status[503] = "Service Unavailable";
  ResponseManager::status[504] = "Gateway Timeout";
  ResponseManager::status[505] = "HTTP Version Not Supported";

  ResponseManager::type["html"] = "text/html";
  ResponseManager::type["htm"] = "text/html";
  ResponseManager::type["shtml"] = "text/html";
  ResponseManager::type["css"] = "text/css";
  ResponseManager::type["xml"] = "text/xml";
  ResponseManager::type["txt"] = "text/plain";
  ResponseManager::type["jad"] = "text/vnd.sun.j2me.app-descriptor";
  ResponseManager::type["wml"] = "text/vnd.wap.wml";
  ResponseManager::type["htc"] = "text/x-component";
  ResponseManager::type["mml"] = "text/mathml";
  // image
  ResponseManager::type["gif"] = "image/gif";
  ResponseManager::type["jpeg"] = "image/jpeg";
  ResponseManager::type["jpg"] = "image/jpeg";
  ResponseManager::type["png"] = "image/png";
  ResponseManager::type["svg"] = "image/svg+xml";
  ResponseManager::type["svgz"] = "image/svg+xml";
  ResponseManager::type["tiff"] = "image/tiff";
  ResponseManager::type["tif"] = "image/tiff";
  ResponseManager::type["wbmp"] = "image/vnd.wap.wbmp";
  ResponseManager::type["webp"] = "image/webp";
  ResponseManager::type["ico"] = "image/x-icon";
  ResponseManager::type["jng"] = "image/x-jng";
  ResponseManager::type["bmp"] = "image/x-ms-bmp";
  // font
  ResponseManager::type["woff"] = "font/woff";
  ResponseManager::type["woff2"] = "font/woff2";
  // application
  ResponseManager::type["js"] = "application/javascript";
  ResponseManager::type["atom"] = "application/atom+xml";
  ResponseManager::type["rss"] = "application/rss+xml";
  ResponseManager::type["json"] = "application/json";
  ResponseManager::type["jar"] = "application/java-archive";
  ResponseManager::type["war"] = "application/java-archive";
  ResponseManager::type["ear"] = "application/java-archive";
  ResponseManager::type["pdf"] = "application/pdf";
  ResponseManager::type["doc"] = "application/msword";
  ResponseManager::type["xls"] = "application/vnd.ms-excel";
  ResponseManager::type["ppt"] = "application/vnd.ms-powerpoint";
  ResponseManager::type["docx"] =
      "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
  ResponseManager::type["xlsx"] =
      "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
  ResponseManager::type["pptx"] =
      "application/"
      "vnd.openxmlformats-officedocument.presentationml.presentation";
  ResponseManager::type["wasm"] = "application/wasm";
  ResponseManager::type["zip"] = "application/zip";
  ResponseManager::type["7z"] = "application/x-7z-compressed";
  ResponseManager::type["cco"] = "application/x-cocoa";
  ResponseManager::type["jardiff"] = "application/x-java-archive-diff";
  ResponseManager::type["jnlp"] = "application/x-java-jnlp-file";
  ResponseManager::type["run"] = "application/x-makeself";
  ResponseManager::type["pl"] = "application/x-perl";
  ResponseManager::type["pm"] = "application/x-perl";
  ResponseManager::type["prc"] = "application/x-pilot";
  ResponseManager::type["pdb"] = "application/x-pilot";
  ResponseManager::type["rar"] = "application/x-rar-compressed";
  ResponseManager::type["rpm"] = "application/x-redhat-package-manager";
  ResponseManager::type["sea"] = "application/x-sea";
  ResponseManager::type["swf"] = "application/x-shockwave-flash";
  ResponseManager::type["sit"] = "application/x-stuffit";
  ResponseManager::type["tcl"] = "application/x-tcl";
  ResponseManager::type["tk"] = "application/x-tcl";
  ResponseManager::type["der"] = "application/x-x509-ca-cert";
  ResponseManager::type["pem"] = "application/x-x509-ca-cert";
  ResponseManager::type["crt"] = "application/x-x509-ca-cert";
  ResponseManager::type["xpi"] = "application/x-xpinstall";
  ResponseManager::type["der"] = "application/x-x509-ca-cert";
  ResponseManager::type["pem"] = "application/x-x509-ca-cert";
  ResponseManager::type["crt"] = "application/x-x509-ca-cert";
  ResponseManager::type["xhtml"] = "application/xhtml+xml";
  ResponseManager::type["xspf"] = "application/xspf+xml";
  // application/octet-stream
  ResponseManager::type["bin"] = "application/octet-stream";
  ResponseManager::type["exe"] = "application/octet-stream";
  ResponseManager::type["dll"] = "application/octet-stream";
  ResponseManager::type["deb"] = "application/octet-stream";
  ResponseManager::type["dmg"] = "application/octet-stream";
  ResponseManager::type["iso"] = "application/octet-stream";
  ResponseManager::type["img"] = "application/octet-stream";
  ResponseManager::type["msi"] = "application/octet-stream";
  ResponseManager::type["msp"] = "application/octet-stream";
  ResponseManager::type["msm"] = "application/octet-stream";
  // audio
  ResponseManager::type["mid"] = "audio/midi";
  ResponseManager::type["midi"] = "audio/midi";
  ResponseManager::type["kar"] = "audio/midi";
  ResponseManager::type["mp3"] = "audio/mpeg";
  ResponseManager::type["ogg"] = "audio/ogg";
  ResponseManager::type["m4a"] = "audio/x-m4a";
  ResponseManager::type["ra"] = "audio/x-realaudio";
  // video
  ResponseManager::type["3gpp"] = "video/3gpp";
  ResponseManager::type["3gp"] = "video/3gpp";
  ResponseManager::type["ts"] = "video/mp2t";
  ResponseManager::type["mp4"] = "video/mp4";
  ResponseManager::type["mpeg"] = "video/mpeg";
  ResponseManager::type["mpg"] = "video/mpeg";
  ResponseManager::type["mov"] = "video/quicktime";
  ResponseManager::type["webm"] = "video/webm";
  ResponseManager::type["flv"] = "video/x-flv";
  ResponseManager::type["m4v"] = "video/x-m4v";
  ResponseManager::type["mng"] = "video/x-mng";
  ResponseManager::type["asx"] = "video/x-ms-asf";
  ResponseManager::type["asf"] = "video/x-ms-asf";
  ResponseManager::type["wmv"] = "video/x-ms-wmv";
  ResponseManager::type["avi"] = "video/x-msvideo";
}