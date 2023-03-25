#include <cassert>
#include <memory>

#include "json/data.h"

namespace Json {

/*!
 * \brief Convert it to specific data type.
 */
int Value::asInt() {
  assert(data->code == ValueBase::kInt);
  auto &x = std::static_pointer_cast<ValueInt>(data)->val;
  return x;
}

/*!
 * \brief Convert it to specific data type.
 */
int Value::asInt64() {
  assert(data->code == ValueBase::kInt);
  auto &x = std::static_pointer_cast<ValueInt>(data)->val;
  return x;
}

bool Value::asBool() {
  assert(data->code == ValueBase::kBool);
  auto &x = std::static_pointer_cast<ValueInt>(data)->val;
  return x;
}

bool Value::isArray() {
  return data->code == ValueBase::kArray;
}

bool Value::isMember(const std::string &key) {
  assert(data->code == ValueBase::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  return m.count(key) != 0;
}

const std::string & Value::asString() {
  assert(data->code == ValueBase::kString);
  auto &str = std::static_pointer_cast<ValueString>(data)->val;
  return str;
}

void Value::add(const std::string &ky, const Value &val) {
  assert(data->code == ValueBase::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  m[ky] = val;
}

void Value::add(const Value &val) {
  assert(data->code == ValueBase::kArray);
  auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
  vec.emplace_back(val);
}

/*!
 * \brief Access the member.
 */
Value &Value::operator[](int x) {
  assert(data->code == ValueBase::kArray);
  auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
  assert(x >= 0 && x < (int) vec.size());
  return vec[x];
}

Value &Value::operator[](const std::string &ky) {
  assert(data->code == ValueBase::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  if (m.count(ky)) {
    return m[ky];
  }
  m[ky] = Value(new ValueBase(ValueBase::kNull));
  return m[ky];
}

Value &Value::operator=(const int &x) {
  data = std::make_shared<ValueInt>(x);
  return *this;
}

Value &Value::operator=(const int64_t &x) {
  data = std::make_shared<ValueInt>(x);
  return *this;
}

Value &Value::operator=(const double &x) {
  data = std::make_shared<ValueDouble>(x);
  return *this;
}

Value &Value::operator=(const float &x) {
  data = std::make_shared<ValueDouble>(x);
  return *this;
}

Value &Value::operator=(const std::string &x) {
  data = std::make_shared<ValueString>(x);
  return *this;
}

Value &Value::operator=(const Value &x) {
  data = x.data;
  return *this;
}

Value::Value(ValueBase::TypeCode ty) {
}

}
