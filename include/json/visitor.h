#pragma once

#include <iostream>

#include "data.h"

namespace json {

/* \brief The visitor class for the visitor pattern */
struct BaseVisitor {
  BaseVisitor() {}
  virtual void Visit(Value<plain::Object>* node) {
    for (auto& elem : *node->As<plain::Object>()) {
      elem.second->Accept(this);
    }
  }
  virtual void Visit(Value<plain::Array>* node) {
    for (auto& elem : *node->As<plain::Array>()) {
      elem->Accept(this);
    }
  }
  virtual void Visit(Value<int64_t>* node) {}
  virtual void Visit(Value<bool>* node) {}
  virtual void Visit(Value<double>* node) {}
  virtual void Visit(Value<std::string>* node) {}
};

/* Visitor specialization */
template <>
inline void Value<bool>::Accept(BaseVisitor* v) {
  v->Visit(this);
}
template <>
inline void Value<double>::Accept(BaseVisitor* v) {
  v->Visit(this);
}
template <>
inline void Value<int64_t>::Accept(BaseVisitor* v) {
  v->Visit(this);
}
template <>
inline void Value<std::string>::Accept(BaseVisitor* v) {
  v->Visit(this);
}
template <>
inline void Value<plain::Array>::Accept(BaseVisitor* v) {
  v->Visit(this);
}
template <>
inline void Value<plain::Object>::Accept(BaseVisitor* v) {
  v->Visit(this);
}

/*! `using' will instantiate the template, which is conflict with
 *   template specialization */
using Object = Value<plain::Object>;
using Int = Value<int64_t>;
using Float = Value<double>;
using Bool = Value<bool>;
using String = Value<std::string>;
using Array = Value<plain::Array>;

/*! \brief The printer visitor */
struct JSONPrinter : BaseVisitor {
  int indent{0};
  std::ostream& os;
  void PrintIndent();
  void Visit(Object* node) override;
  void Visit(Array* node) override;
  void Visit(Int* node) override;
  void Visit(Bool* node) override;
  void Visit(Float* node) override;
  void Visit(String* node) override;

  JSONPrinter(std::ostream& os_) : os(os_) {}
};

}  // namespace json