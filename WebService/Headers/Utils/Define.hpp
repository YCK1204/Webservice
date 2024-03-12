#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <string>
#include <sys/_types/_fd_def.h>

#define MAX_CLIENT_BODY_SIZE 4096
#define MAX_CLIENT_SIZE 20
#define BUFFER_SIZE 2048
#define TIMEOUT 1
#define REQUEST_INTERVAL 2
#define MAX_REQUEST_CNT 10
#define MAX_ROOT_LEN 20

#define CONF_PATH "./Config/default.conf"
#define ERR_CONF "Error : Config FileStream"
#define ERR_SYS_FUNC "Error : System function failed"

extern int maxFd;
extern int numOfLine;
extern unsigned short responseStatus;
extern fd_set event;

using namespace std;

typedef enum {
  GET,
  POST,
  DELETE,
} METHOD;

typedef enum {
  NONE,
  READ,
  WRITE,
  ERROR,
} CLIENT_STATE;

typedef enum {
  AUTOINDEX,
  REDIRECTION,
  ERR,
  NORMAL,
} RESPONSE_STATE;

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
  string total;
  string header;
  string body;
  string line;
  string method;
  string root;
} Request;

typedef struct {
  int fd;
  int port;
  int reqCnt;

  CLIENT_STATE state;
  RESPONSE_STATE responseState;

  bool set_cookie;
  bool delete_cookie;

  string addr;
  string http;
  Request request;
  string redirect;
  string httpVer;
  string fileExtension;

  size_t requestSize;
  size_t bodySize;
  time_t lastActTime;

  Image img;
  Calculator cal;
} CLIENT_DATA;

#endif