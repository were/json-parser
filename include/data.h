#include <vector>
#include <string>
#include <map>

namespace json {

class BaseNode {
  virtual ~BaseNode() {}
  template<typename T> T* As();
};

template<typename T>
class Value : BaseNode {
 public:
  using DataType = T;
 private:
  DataType data;
};

using KVPair = Value<std::map<std::string, BaseNode*>>;
using Int = Value<int64_t>;
using Float = Value<double>;
using Bool = Value<bool>;
using String = Value<std::string>;
using Array = Value<std::vector<BaseNode*>>;

template<typename T>
T* BaseNode::As() {
  if (auto cast = dynamic_cast<Value<T>*>(this)) {
    return &cast->data;
  }
  return nullptr;
}

}