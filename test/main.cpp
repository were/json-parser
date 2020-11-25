#include <cstdio>

#include "json.lex.h"
#include "json.tab.h"

void yyrestart(FILE*);

int main(int argc, char* argv[]) {
  params p;
  JSONrestart(fopen(argv[1], "r"));
  JSONparse(&p);
  json::JSONPrinter printer(std::cout);
  p.data->Accept(&printer);
  delete p.data;
  return 0;
}