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
  
  if (!p.data.isMember("double")) {
    std::cerr << "double member not found" << std::endl;
    return 1;
  } else if (!p.data["double"].isDouble()) {
    std::cerr << "double member is not double" << std::endl;
    return 1;
  } else if (p.data["double"].asDouble() != 123.456) {
    std::cerr << "double member is not 123.456" << std::endl;
    return 1;
  }

  return 0;
}

