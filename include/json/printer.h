#pragma once

#include <iostream>
#include <ostream>
#include <functional>

#include "data.h"

namespace Json {

struct Printer {
  void operator()(const Value &value);
#define VTYPE_MACRO(ty, ...) \
  void print(const Value##ty &);
#include "vtype.inc"
#undef VTYPE_MACRO

  Printer(std::ostream &os);

 private:
  int indent{0};
  std::ostream &os;
  static std::map<int, std::function<void(Printer *, const Value &)>>
    initDispatcher();
};

std::ostream &operator<<(std::ostream &os, const Value &value);

}  // namespace json
