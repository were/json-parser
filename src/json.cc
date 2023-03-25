#include "json/json.h"
#include <cstdio>

namespace Json {

Value parseJSON(const char *fname) {
  params p;
  auto fd = fopen(fname, "r");
  JSONrestart(fd);
  JSONparse(&p);
  fclose(fd);
  return p.data;
}

}

