#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <string>

#define MAX_CLIENT_BODY_SIZE 4096
#define MAX_CLIENT_SIZE 20
#define BUFFER_SIZE 2048

#define CONF_PATH "./Config/default.conf"
#define ERR_CONF "Error : Config File"
#define ERR_SYS_FUNC "Error : System function failed"

using namespace std;

typedef enum {
  GET,
  POST,
  DELETE,
} METHOD;

typedef struct {
  int port;
  long clientBodySize;
  string serverName;
  string indexPath;
  string errorPagePath;
  string host;
  string rootPath;
} SERVER_MEMBER;

typedef struct {
  string domainPath;
  string indexPath;
  string returnPath;
  string cgiPath;
  string rootPath;
  bool isAutoIndex;
  bool methods[3];
} LOCATION_MEMBER;

typedef enum {
  ERROR,
  READ,
  WRITE,
} CLIENT_STATE;

typedef struct {
  string display;
  string result;
} Calculator;

typedef struct {
  char *buf;
  char *binary_request;

  size_t image_size;
} Image;

typedef struct {
  int fd;
  int port;
  int addr[4];
  int request_cnt;

  CLIENT_STATE state;
  bool at;
  bool set_cookie;
  bool delete_cookie;

  string root;
  string http;
  string cookie;
  string method;
  string request;
  string redirect;
  string http_ver;
  string connection;
  string body_method;
  string body_request;
  string file_extension;

  size_t str_len;
  size_t body_size;
  time_t last_active_times;

  Image img;
  Calculator cal;
} CLIENT_DATA;

#endif