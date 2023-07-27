#pragma once

#include <functional>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace Json {

struct ValueBase {
  enum class TypeCode {
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
  virtual ~ValueBase() {}
};

template<typename ty, ValueBase::TypeCode ty_code>
struct ValueImpl : ValueBase {
  using UnderlyingType = ty;
  ValueImpl(const ty &val_) : ValueBase(ty_code), val(val_) {}
  ty val;
};

struct Value;

// Declare each sub-type
#define VTYPE_MACRO(ty_name, ...) \
  using Value##ty_name = ValueImpl<__VA_ARGS__, ValueBase::TypeCode::k##ty_name>;
#include "json/vtypes.inc"
#undef VTYPE_MACRO

struct Value {
  /*!
   * \brief Convert it to specific data type.
   */
  int asInt();
  int64_t asInt64();
  bool asBool();
  double asDouble();
  const std::string &asString();
  /*!
   * \brief If this is a certain instance.
   */
  bool isMember(const std::string &key);
  // isArray and etc.
#define VTYPE_MACRO(ty_name, ...) \
  bool is##ty_name() { return data->code == ValueBase::TypeCode::k##ty_name; }
#include "json/vtypes.inc"
#undef VTYPE_MACRO
  /*!
   * \brief Add a member for object.
   */
  void add(const std::string &ky, const Value &val);
  /*!
   * \brief Add a member for array.
   */
  void append(const Value &val);
  /*!
   * \brief The size of this object.
   */
  int size();
  bool empty();
  /*!
   * \brief Remove all the elements of a array of an object.
   */
  void clear();
  /*!
   * \brief Get members.
   */
  Value get(const std::string &ky);
  Value get(const std::string &ky, const Value &dft);
  /*!
   * \brief Access the member.
   */
  Value &operator[](int);
  Value &operator[](const std::string &ky);
  /*!
   * \brief Set the member.
   */
  Value &operator=(const bool &);
  Value &operator=(const int &);
  Value &operator=(const int64_t &);
  Value &operator=(const uint64_t &);
  Value &operator=(const float &);
  Value &operator=(const double &);
  Value &operator=(const std::string &);
  Value &operator=(const Value &);
  /*!
   * \brief Constructor.
   */
  Value(ValueBase *data_) : data(data_) {}
  Value(ValueBase::TypeCode code);
  Value(const Value &other) : data(other.data) {}
  Value(const bool &);
  Value(const int &);
  Value(const int64_t &);
  Value(const uint64_t &);
  Value(const float &);
  Value(const double &);
  Value(const std::string &);
  Value() {}

  ValueBase *operator->() {
    return data.get();
  }

  friend struct Printer;

  /*!
   * \brief Iterator.
   */
  struct iterator {
    /*!
     * \brief The type from which this iterator is derived.
     */
    ValueBase::TypeCode code{ValueBase::TypeCode::kNull};


    iterator &operator++();
    bool operator!= (const iterator &other);
    Value& operator*() const;

    union {
      ValueArray::UnderlyingType::iterator v_iter;
      ValueObject::UnderlyingType::iterator m_iter;
    };

    iterator() {}

    iterator(const ValueArray::UnderlyingType::iterator &v) {
      code = ValueBase::TypeCode::kArray;
      v_iter = v;
    }

    iterator(const ValueObject::UnderlyingType::iterator &m) {
      code = ValueBase::TypeCode::kObject;
      m_iter = m;
    }

    /*!
     * \brief If it iterates over an object, it has a key.
     */
    Value key();

    iterator(const iterator &other);
  };
  iterator begin();
  iterator end();

 private:
  /*!
   * \brief The data to be held.
   */
  std::shared_ptr<ValueBase> data;
};

} // namespace Json
