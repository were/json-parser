#include <cassert>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <iostream>

#include "json/value.h"

namespace Json {

/*!
 * \brief Convert it to specific data type.
 */
int Value::asInt() {
  assert(data->code == ValueBase::TypeCode::kInt);
  auto &x = std::static_pointer_cast<ValueInt>(data)->val;
  return x;
}

/*!
 * \brief Convert it to specific data type.
 */
int Value::asInt64() {
  assert(data->code == ValueBase::TypeCode::kInt);
  auto &x = std::static_pointer_cast<ValueInt>(data)->val;
  return x;
}

double Value::asDouble() {
  assert(data->code == ValueBase::TypeCode::kDouble);
  auto &x = std::static_pointer_cast<ValueDouble>(data)->val;
  return x;
}

bool Value::asBool() {
  assert(data->code == ValueBase::TypeCode::kBool);
  auto &x = std::static_pointer_cast<ValueInt>(data)->val;
  return x;
}

bool Value::isMember(const std::string &key) {
  assert(data->code == ValueBase::TypeCode::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  return m.count(key) != 0;
}

const std::string & Value::asString() {
  assert(data->code == ValueBase::TypeCode::kString);
  auto &str = std::static_pointer_cast<ValueString>(data)->val;
  return str;
}

void Value::add(const std::string &ky, const Value &val) {
  assert(data->code == ValueBase::TypeCode::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  m[ky] = val;
}

void Value::append(const Value &val) {
  assert(data->code == ValueBase::TypeCode::kArray);
  auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
  vec.emplace_back(val);
}

/*!
 * \brief Access the member.
 */
Value &Value::operator[](int x) {
  assert(data->code == ValueBase::TypeCode::kArray);
  auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
  assert(x >= 0 && x < (int) vec.size());
  return vec[x];
}

Value &Value::operator[](const std::string &ky) {
  assert(data->code == ValueBase::TypeCode::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  if (m.count(ky)) {
    return m[ky];
  }
  m[ky] = Value(new ValueNull(nullptr));
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

Value &Value::operator=(const uint64_t &x) {
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


Value::Value(const int &x) {
  data = std::make_shared<ValueInt>(x);
}

Value::Value(const int64_t &x) {
  data = std::make_shared<ValueInt>(x);
}

Value::Value(const uint64_t &x) {
  data = std::make_shared<ValueInt>(x);
}

Value::Value(const double &x) {
  data = std::make_shared<ValueDouble>(x);
}

Value::Value(const float &x) {
  data = std::make_shared<ValueDouble>(x);
}

Value::Value(const std::string &x) {
  data = std::make_shared<ValueString>(x);
}


Value::Value(ValueBase::TypeCode ty) {
}

Value Value::get(const std::string &ky) {
  return this->operator[](ky);
}

Value Value::get(const std::string &ky, const Value &dft) {
  assert(data->code == ValueBase::TypeCode::kObject);
  auto &m = std::static_pointer_cast<ValueObject>(data)->val;
  if (m.count(ky)) {
    return m[ky];
  }
  return dft;
}

int Value::size() {
  if (data->code == ValueBase::TypeCode::kArray) {
    auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
    return vec.size();
  }
  if (data->code == ValueBase::TypeCode::kObject) {
    auto &m = std::static_pointer_cast<ValueObject>(data)->val;
    return m.size();
  }
  assert(false);
  abort();
}

bool Value::empty() {
  if (data->code == ValueBase::TypeCode::kNull) {
    return true;
  }
  return size() == 0;
}

void Value::clear() {
  if (data->code == ValueBase::TypeCode::kArray) {
    auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
    vec.clear();
  }
  if (data->code == ValueBase::TypeCode::kObject) {
    auto &m = std::static_pointer_cast<ValueObject>(data)->val;
    m.clear();
  }
  std::cerr
    << "[WARNING] clearing a value which is neither an array nor object!";
}

Value::iterator &Value::iterator::operator++() {
  switch (code) {
  case ValueBase::TypeCode::kObject:
    this->m_iter++;
    break;
  case ValueBase::TypeCode::kArray:
    this->v_iter++;
  default:
    break;
  }
  return *this;
}

Value &Value::iterator::operator*() const {
  switch (code) {
  case ValueBase::TypeCode::kObject:
    return m_iter->second;
  case ValueBase::TypeCode::kArray:
    return *v_iter;
  default:
    break;
  }
  assert(false && "null iterator");
  abort();
}

bool Value::iterator::operator!=(const iterator &other) {
  assert(code == other.code);
  switch (code) {
  case ValueBase::TypeCode::kObject:
    return m_iter != other.m_iter;
  case ValueBase::TypeCode::kArray:
    return v_iter != other.v_iter;
  default:
    break;
  }
  return false;
}

Value::iterator::iterator(const Value::iterator &other) {
  code = other.code;
  switch (code) {
  case ValueBase::TypeCode::kObject:
    m_iter = other.m_iter;
    break;
  case ValueBase::TypeCode::kArray:
    v_iter = other.v_iter;
  default:
    code = ValueBase::TypeCode::kNull;
    break;
  }
}


Value::iterator Value::begin() {
  if (ValueBase::TypeCode::kArray == data->code) {
    auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
    return iterator(vec.begin());
  }
  if (ValueBase::TypeCode::kObject == data->code) {
    auto &m = std::static_pointer_cast<ValueObject>(data)->val;
    return iterator(m.begin());
  }
  return iterator();
}

Value::iterator Value::end() {
  if (ValueBase::TypeCode::kArray == data->code) {
    auto &vec = std::static_pointer_cast<ValueArray>(data)->val;
    return iterator(vec.end());
  }
  if (ValueBase::TypeCode::kObject == data->code) {
    auto &m = std::static_pointer_cast<ValueObject>(data)->val;
    return iterator(m.end());
  }
  return iterator();
}

Value Value::iterator::key() {
  assert(code == ValueBase::TypeCode::kObject);
  return m_iter->first;
}

}
