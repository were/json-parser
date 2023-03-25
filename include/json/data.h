#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

namespace Json {

struct ValueBase {
  enum TypeCode {
    kInt,
    kString,
    kArray,
    kObject,
    kDouble,
    kBool,
    kNull,
  };
  TypeCode code;
  ValueBase(TypeCode code_) : code(code_) {}
};

template<typename ty, ValueBase::TypeCode ty_code>
struct ValueImpl : ValueBase {
  ValueImpl(const ty &val_) : ValueBase(ty_code), val(val_) {}
  ty val;
};

struct Value;

#define VTYPE_MACRO(ty_name, ...) \
  using Value##ty_name = ValueImpl<__VA_ARGS__, ValueBase::k##ty_name>;
#include "vtype.inc"
#undef VTYPE_MACRO

struct Value {
  /*!
   * \brief Convert it to specific data type.
   */
  int asInt();
  int asInt64();
  bool asBool();
  bool isArray();
  bool isMember(const std::string &key);
  const std::string &asString();
  void add(const std::string &ky, const Value &val);
  void add(const Value &val);
  /*!
   * \brief Access the member.
   */
  Value &operator[](int);
  Value &operator[](const std::string &ky);
  /*!
   * \brief Set the member.
   */
  Value &operator=(const int &);
  Value &operator=(const int64_t &);
  Value &operator=(const float &);
  Value &operator=(const double &);
  Value &operator=(const std::string &);
  Value &operator=(const Value &);
  /*!
   * \brief Constructor.
   */
  Value(ValueBase *data_) : data(data_) {}
  Value(ValueBase::TypeCode code);

  Value() {}

  ValueBase *operator->() {
    return data.get();
  }

  friend struct Printer;

 private:
  /*!
   * \brief The data to be held.
   */
  std::shared_ptr<ValueBase> data;
};

} // namespace Json
