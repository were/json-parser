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
  
  if (p.data.isMember("new_member")) {
    std::cerr << "new_member member found" << std::endl;
    return 1;
  }

  p.data["new_member"] = "new_value";

  if (!p.data.isMember("new_member")) {
    std::cerr << "new_member member not found" << std::endl;
    return 1;
  } else if (!p.data["new_member"].isString()) {
    std::cerr << "new_member member is not string" << std::endl;
    return 1;
  } else if (p.data["new_member"].asString() != "new_value") {
    std::cerr << "new_member member is not \"new_value\". Instead is: " << p.data["new_member"].asString() << std::endl;
    return 1;
  }

  return 0;
}

