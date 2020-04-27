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

/*! \brief The basic class of JSON data structure */
class BaseNode {
 public:
  /*! \brief The virtual method for the visitor pattern */
  virtual void Accept(BaseVisitor *) = 0;
  /*! \brief The method for data cast */
  template<typename T> inline T* As();
  /*! \brief RTTI required */
  virtual ~BaseNode() {}
};

/*! \brief The derived class of JSON data structure. This template will
           be instantiated in visitor because of the C++ constraints */
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