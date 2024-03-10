#include "../Headers/Http.hpp"

int numOfLine;

int main(int ac, char *av[]) {
  if (ac > 2) {
    FT_THROW("Too many argument", av[2]);
  }
  string path = (ac == 1 ? CONF_PATH : av[1]);

  Http http(path);
  return 0;
}