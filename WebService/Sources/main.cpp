#include "../Headers/Contents/Http.hpp"
#include <sys/_types/_fd_def.h>

int numOfLine;
int maxFd;
unsigned short responseStatus;
fd_set event;
Http http;

int main(int ac, char *av[]) {
  if (ac > 2) {
    FT_THROW("Too many argument", av[2]);
  }
  string path = (ac == 1 ? CONF_PATH : av[1]);

  Manager::Init();
  http.StartWebService(path);
  return 0;
}