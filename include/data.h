#pragma once

#include <vector>
#include <string>
#include <map>

namespace json {

class BaseNode;

}
namespace plain {

using Object = std::map<std::string, json::BaseNode*>;
using Array = std::vector<json::BaseNode*>;

}

namespace json {

class BaseVisitor;

class BaseNode {
 public:
  virtual void Accept(BaseVisitor *) = 0;
  template<typename T> inline T* As();
  virtual ~BaseNode() {}
};

template<typename T>
class Value : public BaseNode {
 public:
  using DataType = T;
  Value(const T &data_) : data(data_) {}
  ~Value() {}
  friend class BaseNode;
  inline void Accept(BaseVisitor *visitor) override;
};

template<typename T>
class Value : public BaseNode {
 public:
  using DataType = T;
  Value(const T &data_) : data(data_) {}
  ~Value() {}
  friend class BaseNode;
  inline void Accept(BaseVisitor *visitor) override;
 private:
  DataType data;
};

template<typename T>
inline T* BaseNode::As() {
  if (auto cast = dynamic_cast<Value<T>*>(this)) {
    return &cast->data;
  }
  return nullptr;
}

}