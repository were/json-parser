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

  if (!p.data.isMember("number64")) {
    std::cerr << "number64 member not found" << std::endl;
    return 1;
  } else if (!p.data["number64"].isInt()) {
    std::cerr << "number64 member is not number" << std::endl;
    return 1;
  } else if (p.data["number64"].asInt64() != 1099511627776) {
    std::cerr << "number64 member is not 1099511627776 instead: " << p.data["number64"].asInt64() <<std::endl;
    return 1;
  }

  return 0;
}

