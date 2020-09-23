#include "json/visitor.h"

namespace json {

void JSONPrinter::PrintIndent() {
  os << std::string(indent, ' ');
}

void JSONPrinter::Visit(Object *node) {

  os << "{\n";
  indent += 2;
  bool first = true;
  for (auto &elem : *node->As<plain::Object>()) {
    if (!first) os << ",\n";
    PrintIndent();
    os << '"' << elem.first << '"' << ": ";
    elem.second->Accept(this);
    first = false;
  }
  os << "\n";
  indent -= 2;
  PrintIndent();
  os << "}";
}

void JSONPrinter::Visit(Array *node) {
  bool first = true;
  os << "[";
  for (auto &elem : *node->As<plain::Array>()) {
    if (!first) os << ", ";
    elem->Accept(this);
    first = false;
  }
  os << "]";
}

void JSONPrinter::Visit(Int *node) {
  os << *node->As<int64_t>();
}

void JSONPrinter::Visit(Bool *node) {
  os << ((*node->As<bool>()) ? "\"true\"" : "\"false\"");
}

void JSONPrinter::Visit(Float *node) {
  os << (*node->As<double>());
}

void JSONPrinter::Visit(String *node) {
  os << '"' << (*node->As<std::string>()) << '"';
}

}