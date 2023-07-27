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


  p.data["new_member_bool"] = true;
  p.data["new_member_int"] = 123;
  p.data["new_member_char"] = "new_value";
  p.data["new_member"] = std::string("new_value");

  std::cout << p.data << std::endl;

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


  if (!p.data.isMember("new_member_bool")) {
    std::cerr << "new_member_bool member not found" << std::endl;
    return 1;
  } else if (!p.data["new_member_bool"].isBool()) {
    std::cerr << "new_member_bool member is not bool" << std::endl;
    return 1;
  } else if (p.data["new_member_bool"].asBool() != true) {
    std::cerr << "new_member_bool member is not \"true\". Instead is: " << p.data["new_member_bool"].asBool() << std::endl;
    return 1;
  }


  if (!p.data.isMember("new_member_char")) {
    std::cerr << "new_member member not found" << std::endl;
    return 1;
  } else if (!p.data["new_member_char"].isString()) {
    std::cerr << "new_member member is not string" << std::endl;
    return 1;
  } else if (p.data["new_member_char"].asString() != "new_value") {
    std::cerr << "new_member_char member is not \"new_value\". Instead is: " << p.data["new_member_char"].asString() << std::endl;
    return 1;
  }


  if (!p.data.isMember("new_member_int")) {
    std::cerr << "new_member_int member not found" << std::endl;
    return 1;
  } else if (!p.data["new_member_int"].isInt()) {
    std::cerr << "new_member_int member is not int" << std::endl;
    return 1;
  } else if (p.data["new_member_int"].asInt() != 123) {
    std::cerr << "new_member_int member is not \"123\". Instead is: " << p.data["new_member_int"].asInt() << std::endl;
    return 1;
  }

  return 0;
}
