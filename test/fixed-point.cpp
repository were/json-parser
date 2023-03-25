#include <iostream>

#include "json.lex.h"
#include "json.tab.h"
#include "json/printer.h"

void yyrestart(FILE*);

int main(int argc, char* argv[]) {
  params p;
  JSONrestart(fopen(argv[1], "r"));
  JSONparse(&p);
  std::cout << p.data << std::endl;
  return 0;
}
