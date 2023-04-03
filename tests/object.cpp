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

  if (!p.data.isMember("object")) {
    std::cerr << "object member found" << std::endl;
    return 1;
  } else if (!p.data["object"].isObject()) {
    std::cerr << "object member is not object" << std::endl;
    return 1;
  } else if (p.data["object"].size() != 3) {
    std::cerr << "object member is not size 3" << std::endl;
    return 1;
  } else if (p.data["object"]["a"].asString() != "b") {
    std::cerr << "object member is not {\"a\": \"b\", \"c\": \"d\", \"e\": \"f\"}" << std::endl;
    return 1;
  } else if (p.data["object"]["c"].asString() != "d") {
    std::cerr << "object member is not {\"a\": \"b\", \"c\": \"d\", \"e\": \"f\"}" << std::endl;
    return 1;
  } else if (p.data["object"]["e"].asString() != "f") {
    std::cerr << "object member is not {\"a\": \"b\", \"c\": \"d\", \"e\": \"f\"}" << std::endl;
    return 1;
  }

  return 0;
}

