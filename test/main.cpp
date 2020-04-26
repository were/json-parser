#include <cstdio>
#include "json.tab.h"

void yyrestart(FILE*);

int main(int argc, char **argv) {
  FILE *f = fopen(argv[1], "r");
  yyrestart(f);
  struct Param p;
  yyparse(&p);
}