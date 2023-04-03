#include <iostream>

#include "json.lex.h"
#include "json.tab.h"
#include "json/printer.h"

void yyrestart(FILE*);

/* This is the Json file we are going to parse */

/*
  {
    "string": "Hello There",
    "boolean": true,
    "number": 123,
    "double": 123.456,
    "array": [
        "one",
        "two",
        "three"
    ]
    "object": {
        "a": "b",
        "c": "d",
        "e": "f"
    },
  }
*/

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <json file>" << std::endl;
    return 1;
  }

  params p;
  JSONrestart(fopen(argv[1], "r"));
  JSONparse(&p);

  std::cout << p.data << std::endl;

  if (!p.data.isMember("number")) {
    std::cerr << "number member not found" << std::endl;
    return 1;
  } else if (!p.data["number"].isInt()) {
    std::cerr << "number member is not number" << std::endl;
    return 1;
  } else if (p.data["number"].asInt() != 123) {
    std::cerr << "number member is not 123" << std::endl;
    return 1;
  }

  return 0;
}

