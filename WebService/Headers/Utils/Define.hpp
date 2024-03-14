#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <string>
#include <sys/_types/_fd_def.h>

#define TIMEOUT 1
#define MAX_ROOT_LEN 50
#define BUFFER_SIZE 2048
#define REQUEST_INTERVAL 2
#define MAX_REQUEST_CNT 10
#define MAX_CLIENT_SIZE 20
#define MAX_CLIENT_REQUEST_SIZE 10000

#define CONF_PATH "./Config/default.conf"
#define ERR_CONF "Error : Config FileStream"
#define ERR_SYS_FUNC "Error : System function failed"

extern int maxFd;
extern int numOfLine;
extern fd_set event;
extern unsigned short responseStatus;

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
  JS,
  ERR,
  CSS,
  IMG,
  NORMAL,
  AUTOINDEX,
  REDIRECTION,
} RESPONSE_STATE;

typedef struct {
  int port;
  long clientBodySize;
  string host;
  string rootPath;
  string indexPath;
  string serverName;
  string jsRootPath;
  string cssRootPath;
  string imgRootPath;
  string errorPagePath;
} SERVER_MEMBER;

typedef struct {
  bool methods[3];
  bool isAutoIndex;
  string cgiPath;
  string rootPath;
  string indexPath;
  string domainPath;
  string returnPath;
} LOCATION_MEMBER;

typedef struct {
  string root;
  string body;
  string line;
  string total;
  string header;
  string method;
  size_t bodySize;
} Request;

typedef struct {
  int fd;
  int port;
  int reqCnt;

  CLIENT_STATE state;
  RESPONSE_STATE responseState;

  string addr;
  string httpVer;
  string fileExtension;

  time_t lastActTime;

} CLIENT_DATA;

#endif