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
  
  if (!p.data.isMember("string")) {
    std::cerr << "string member not found" << std::endl;
    return 1;
  } else if (!p.data["string"].isString()) {
    std::cerr << "string member is not string" << std::endl;
    return 1;
  } else if (p.data["string"].asString() != "Hello There") {
    std::cerr << "string member is not \"Hello There\". Instead is: " << p.data["string"].asString() << std::endl;
    return 1;
  }

  if (!p.data.isMember("boolean")) {
    std::cerr << "boolean member not found" << std::endl;
    return 1;
  } else if (!p.data["boolean"].isBool()) {
    std::cerr << "boolean member is not bool" << std::endl;
    return 1;
  } else if (p.data["boolean"].asBool() != true) {
    std::cerr << "boolean member is not true" << std::endl;
    return 1;
  }

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

  {
    auto object = p.data["object"];
    int count = 0;
    auto it = object.begin();
    for (; it != object.end(); ++it) {
      count++;
    }
    if (count != 3) {
      std::cerr << "object member is not size 3" << std::endl;
      return 1;
    }
  }

  return 0;
}

