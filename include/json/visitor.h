#pragma once

#include <iostream>
#include "data.h"

namespace json {

/* \brief The visitor class for the visitor pattern */
struct BaseVisitor {
  BaseVisitor() {}
  virtual void Visit(Value<plain::Object> *node) {
    for (auto &elem : *node->As<plain::Object>()) {
      elem.second->Accept(this);
    }
  }
  virtual void Visit(Value<plain::Array> *node) {
    for (auto &elem : *node->As<plain::Array>()) {
      elem->Accept(this);
    }
  }
  virtual void Visit(Value<int64_t> *node) {}
  virtual void Visit(Value<bool> *node) {}
  virtual void Visit(Value<double> *node) {}
  virtual void Visit(Value<std::string> *node) {}
};

template<> inline void Value<int64_t>::Accept(BaseVisitor *v) { v->Visit(this); }
template<> inline void Value<bool>::Accept(BaseVisitor *v) { v->Visit(this); }
template<> inline void Value<plain::Array>::Accept(BaseVisitor *v) { v->Visit(this); }
template<> inline void Value<plain::Object>::Accept(BaseVisitor *v) { v->Visit(this); }
template<> inline void Value<double>::Accept(BaseVisitor *v) { v->Visit(this); }
template<> inline void Value<std::string>::Accept(BaseVisitor *v) { v->Visit(this); }

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
  std::ostream &os;
  JSONPrinter(std::ostream &os_) : os(os_) {}

  void Visit(Object *node) override {
    os << "{";
    bool first = true;
    for (auto &elem : *node->As<plain::Object>()) {
      if (!first) os << ",\n";
      os << '"' << elem.first << "\":";
      elem.second->Accept(this);
      first = false;
    }
    os << "}\n";
  }
  void Visit(Array *node) override {
    bool first = true;
    os << "[";
    for (auto &elem : *node->As<plain::Array>()) {
      if (!first) os << ", ";
      elem->Accept(this);
      first = false;
    }
    os << "]\n";
  }
  virtual void Visit(Int *node) override {
    os << *node->As<int64_t>();
  }
  virtual void Visit(Bool *node) override {
    os << (*node->As<bool>()) ? "\"true\"" : "\"false\"";
  }
  virtual void Visit(Float *node) {
    os << (*node->As<double>());
  }
  virtual void Visit(String *node) {
    os << '"' << (*node->As<std::string>()) << '"';
  }
};
}