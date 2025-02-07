/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <folly/Optional.h>
#include <thrift/lib/cpp2/GeneratedHeaderHelper.h>
#include <thrift/lib/cpp2/Thrift.h>
#include <thrift/lib/cpp2/gen/module_types_h.h>
#include <thrift/lib/cpp2/protocol/Protocol.h>


// BEGIN declare_enums

// END declare_enums
// BEGIN struct_indirection

// END struct_indirection
// BEGIN forward_declare
namespace cpp2 {
class House;
class Field;
} // cpp2
// END forward_declare
// BEGIN typedefs
namespace cpp2 {
typedef int64_t ColorID;

} // cpp2
// END typedefs
// BEGIN hash_and_equal_to
// END hash_and_equal_to
namespace cpp2 {
class House final : private apache::thrift::detail::st::ComparisonOperators<House> {
 public:

  House() :
      id(0) {}
  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  House(apache::thrift::FragileConstructor,  ::cpp2::ColorID id__arg, ::std::string houseName__arg, ::std::set< ::cpp2::ColorID> houseColors__arg);
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<1, _T> arg) {
    id = arg.extract();
  }
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<2, _T> arg) {
    houseName = arg.extract();
  }
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<3, _T> arg) {
    houseColors = arg.extract();
  }

  House(House&&) = default;

  House(const House&) = default;

  House& operator=(House&&) = default;

  House& operator=(const House&) = default;
  void __clear();
   ::cpp2::ColorID id;
  ::std::string houseName;
  folly::Optional<::std::set< ::cpp2::ColorID>> houseColors;
  bool operator==(const House& rhs) const;
  bool operator<(const House& rhs) const;

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

  friend class ::apache::thrift::Cpp2Ops< House >;
};

void swap(House& a, House& b);

template <class Protocol_>
uint32_t House::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

} // cpp2
namespace cpp2 {
class Field final : private apache::thrift::detail::st::ComparisonOperators<Field> {
 public:

  Field() :
      id(0),
      fieldType(5) {}
  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  Field(apache::thrift::FragileConstructor,  ::cpp2::ColorID id__arg, int32_t fieldType__arg);
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<1, _T> arg) {
    id = arg.extract();
  }
  template <typename _T>
  void __set_field(::apache::thrift::detail::argument_wrapper<2, _T> arg) {
    fieldType = arg.extract();
  }

  Field(Field&&) = default;

  Field(const Field&) = default;

  Field& operator=(Field&&) = default;

  Field& operator=(const Field&) = default;
  void __clear();
   ::cpp2::ColorID id;
  int32_t fieldType;
  bool operator==(const Field& rhs) const;
  bool operator<(const Field& rhs) const;

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

  friend class ::apache::thrift::Cpp2Ops< Field >;
};

void swap(Field& a, Field& b);

template <class Protocol_>
uint32_t Field::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

} // cpp2
