#include <iostream>

#include "json.lex.h"
#include "json.tab.h"
#include "json/printer.h"

void yyrestart(FILE*);

int main(int argc, char* argv[]) {
  Json::Value data;

  data["string"] = "Hello There";

  if (!data.isMember("string")) {
    std::cerr << "string member not found" << std::endl;
    return 1;
  } else if (!data["string"].isString()) {
    std::cerr << "string member is not string" << std::endl;
    return 1;
  } else if (data["string"].asString() != "Hello There") {
    std::cerr << "string member is not 'Hello There'" << std::endl;
    return 1;
  }

  return 0;
}

