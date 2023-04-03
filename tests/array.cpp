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

  if (!p.data.isMember("array")) {
    std::cerr << "array member not found" << std::endl;
    return 1;
  } else if (!p.data["array"].isArray()) {
    std::cerr << "array member is not array" << std::endl;
    return 1;
  } else if (p.data["array"].size() != 3) {
    std::cerr << "array member is not size 3" << std::endl;
    return 1;
  } else if (p.data["array"][0].asString() != "one") {
    std::cerr << "array member is not [\"one\", \"two\", \"three\"]" << std::endl;
    return 1;
  } else if (p.data["array"][1].asString() != "two") {
    std::cerr << "array member is not [\"one\", \"two\", \"three\"]" << std::endl;
    return 1;
  } else if (p.data["array"][2].asString() != "three") {
    std::cerr << "array member is not [\"one\", \"two\", \"three\"]" << std::endl;
    return 1;
  }

  return 0;
}

