#include <iostream>

#include "json.lex.h"
#include "json.tab.h"
#include "json/printer.h"

void yyrestart(FILE*);

int main(int argc, char* argv[]) {
  Json::Value data(new Json::ValueObject({}));

  data["string"] = "Hello There";

  std::cout << data << std::endl;

  if (!data.isMember("string")) {
    std::cerr << "string member not found" << std::endl;
    return 1;
  } else if (data["string"].asString() != "Hello There") {
    std::cerr << "string member has wrong value" << std::endl;
    return 1;
  }

  return 0;
}

