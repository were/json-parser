#include <iostream>

#include "json.lex.h"
#include "json.tab.h"
#include "json/printer.h"

void yyrestart(FILE*);

// f(f(x))
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <json file>" << std::endl;
    return 0;
  }

  params p;
  JSONrestart(fopen(argv[1], "r"));
  JSONparse(&p);
  std::cout << p.data << std::endl;
  return 0;
}

