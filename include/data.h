<<<<<<< HEAD
#pragma once

=======
>>>>>>> it is compiling but crashing
#include <vector>
#include <string>
#include <map>

namespace json {

<<<<<<< HEAD
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
=======
class BaseNode {
  virtual ~BaseNode() {}
  template<typename T> T* As();
};

template<typename T>
class Value : BaseNode {
 public:
  using DataType = T;
>>>>>>> it is compiling but crashing
 private:
  DataType data;
};

<<<<<<< HEAD
template<typename T>
inline T* BaseNode::As() {
=======
using KVPair = Value<std::map<std::string, BaseNode*>>;
using Int = Value<int64_t>;
using Float = Value<double>;
using Bool = Value<bool>;
using String = Value<std::string>;
using Array = Value<std::vector<BaseNode*>>;

template<typename T>
T* BaseNode::As() {
>>>>>>> it is compiling but crashing
  if (auto cast = dynamic_cast<Value<T>*>(this)) {
    return &cast->data;
  }
  return nullptr;
}

}