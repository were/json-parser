#include <cassert>
#include <memory>
#include <ostream>
#include <type_traits>

#include "json/printer.h"
#include "json/value.h"

namespace Json {

#define INDENT std::string(indent, ' ')

std::map<int, std::function<void(Printer *, const Value &)>>
Printer::initDispatcher() {
  std::map<int, std::function<void(Printer *, const Value &)>> res;
#define VTYPE_MACRO(ty, ...) \
  do { \
    auto f = [] (Printer *p, const Value &value) -> void { \
      assert(value.data->code == ValueBase::TypeCode::k##ty); \
      p->print(*std::static_pointer_cast<Value##ty>(value.data)); \
    }; \
    auto code = static_cast<std::underlying_type_t<ValueBase::TypeCode>>( \
      ValueBase::TypeCode::k##ty); \
    res[code] = f; \
  } while (false);
#include "json/vtypes.inc"
#undef VTYPE_MACRO
  return res;
}

Printer::Printer(std::ostream &os_) : os(os_) {}

std::ostream &operator<<(std::ostream &os, const Value &value) {
  Printer printer(os);
  printer(value);
  return os;
}

void Printer::operator()(const Value &value) {
  static auto dispatcher = initDispatcher();

  auto code = static_cast<std::underlying_type_t<ValueBase::TypeCode>>(
    value.data->code);
  dispatcher[code](this, value);
}

void Printer::print(const ValueObject &obj) {
  os << "{\n";
  indent += 2;
  bool first = true;
  for (auto& elem : obj.val) {
    if (!first) os << ",\n";
    os << INDENT;
    os << '"' << elem.first << '"' << ": ";
    (*this)(elem.second);
    first = false;
  }
  os << "\n";
  indent -= 2;
  os << INDENT << "}";
}

void Printer::print(const ValueArray &array) {
  bool first = true;
  os << "[";
  for (auto& elem : array.val) {
    if (!first) os << ", ";
    (*this)(elem);
    first = false;
  }
  os << "]";
}

void Printer::print(const ValueInt &vi) { os << vi.val; }

void Printer::print(const ValueBool &b) {
  os << (b.val ? "\"true\"" : "\"false\"");
}

void Printer::print(const ValueDouble &dbl) { os << dbl.val; }

void Printer::print(const ValueString &str) { os << '"' << str.val << '"'; }

void Printer::print(const ValueNull &null) { os << "null"; }

#undef INDENT

}  // namespace json
