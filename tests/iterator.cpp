#include <iostream>

#include "json.lex.h"
#include "json.tab.h"
#include "json/printer.h"

void yyrestart(FILE*);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <json file>" << std::endl;
    return 1;
  }

  params p;
  JSONrestart(fopen(argv[1], "r"));
  JSONparse(&p);

  std::cout << p.data << std::endl;

  int count = 0;
  for (auto it = p.data["object"].begin(); it != p.data["object"].end(); ++it) {
    count++;
  }

  if (count != 3) {
    std::cerr << "object member is not size 3" << std::endl;
    return 1;
  }
  

  return 0;
}

