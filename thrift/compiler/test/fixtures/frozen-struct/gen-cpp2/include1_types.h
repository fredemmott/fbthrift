/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/GeneratedHeaderHelper.h>
#include <thrift/lib/cpp2/Thrift.h>
#include <thrift/lib/cpp2/gen/module_types_h.h>
#include <thrift/lib/cpp2/protocol/Protocol.h>


// BEGIN declare_enums

// END declare_enums
// BEGIN struct_indirection

// END struct_indirection
// BEGIN forward_declare
namespace some { namespace ns {
class IncludedA;
}} // some::ns
// END forward_declare
// BEGIN typedefs

// END typedefs
// BEGIN hash_and_equal_to
// END hash_and_equal_to
namespace some { namespace ns {
class IncludedA final : private apache::thrift::detail::st::ComparisonOperators<IncludedA> {
 public:

  IncludedA() :
      i32Field(0) {}
  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  IncludedA(apache::thrift::FragileConstructor, int32_t i32Field__arg, ::std::string strField__arg);
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<1, _T> arg) {
    i32Field = arg.extract();
    __isset.i32Field = true;
  }
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<2, _T> arg) {
    strField = arg.extract();
    __isset.strField = true;
  }

  IncludedA(IncludedA&&) = default;

  IncludedA(const IncludedA&) = default;

  IncludedA& operator=(IncludedA&&) = default;

  IncludedA& operator=(const IncludedA&) = default;
  void __clear();
  int32_t i32Field;
  ::std::string strField;

  struct __isset {
    bool i32Field;
    bool strField;
  } __isset = {};
  bool operator==(const IncludedA& rhs) const;
  bool operator<(const IncludedA& rhs) const;

  int32_t get_i32Field() const {
    return i32Field;
  }

  int32_t& set_i32Field(int32_t i32Field_) {
    i32Field = i32Field_;
    __isset.i32Field = true;
    return i32Field;
  }

  const ::std::string& get_strField() const& {
    return strField;
  }

  ::std::string get_strField() && {
    return std::move(strField);
  }

  template <typename T_IncludedA_strField_struct_setter = ::std::string>
  ::std::string& set_strField(T_IncludedA_strField_struct_setter&& strField_) {
    strField = std::forward<T_IncludedA_strField_struct_setter>(strField_);
    __isset.strField = true;
    return strField;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  template <class Protocol_>
  void readNoXfer(Protocol_* iprot);

  friend class ::apache::thrift::Cpp2Ops< IncludedA >;
};

void swap(IncludedA& a, IncludedA& b);

template <class Protocol_>
uint32_t IncludedA::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

}} // some::ns
