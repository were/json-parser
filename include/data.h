#pragma once

#include <vector>
#include <string>
#include <map>

namespace json {

class BaseNode {
 public:
  virtual ~BaseNode() {}
  template<typename T> inline T* As();
};

template<typename T>
class Value : public BaseNode {
 public:
  using DataType = T;
  Value(const T &data_) : data(data_) {}
  ~Value() {}
 private:
  DataType data;
};

using Object = Value<std::map<std::string, BaseNode*>>;
using Int = Value<int64_t>;
using Float = Value<double>;
using Bool = Value<bool>;
using String = Value<std::string>;
using Array = Value<std::vector<BaseNode*>>;

template<typename T>
inline T* BaseNode::As() {
  if (auto cast = dynamic_cast<Value<T>*>(this)) {
    return &cast->data;
  }
  return nullptr;
}

}