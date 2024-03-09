#ifndef DEFINE_HPP
#define DEFINE_HPP

#define MAX_CLIENT_BODY_SIZE 4096
#define MAX_CLIENT_SIZE 20
#define BUFFER_SIZE 2048

#define CONF_PATH "./Config/default.conf"
#define ERR_CONF "Error : Config File"
#define ERR_SYS_FUNC "Error : System function failed"

typedef enum {
  GET,
  POST,
  DELETE,
} METHOD;

#endif