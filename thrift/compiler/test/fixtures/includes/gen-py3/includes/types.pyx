#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#
cimport cython as __cython
from cpython.bytes cimport PyBytes_AsStringAndSize
from cpython.object cimport PyTypeObject, Py_LT, Py_LE, Py_EQ, Py_NE, Py_GT, Py_GE
from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from libcpp.iterator cimport inserter as cinserter
from cpython cimport bool as pbool
from libc.stdint cimport int8_t, int16_t, int32_t, int64_t, uint32_t
from cython.operator cimport dereference as deref, preincrement as inc, address as ptr_address
import thrift.py3.types
cimport thrift.py3.types
cimport thrift.py3.exceptions
from thrift.py3.types import NOTSET as __NOTSET
from thrift.py3.types cimport (
    translate_cpp_enum_to_python,
    SetMetaClass as __SetMetaClass,
    constant_shared_ptr,
    default_inst,
)
cimport thrift.py3.std_libcpp as std_libcpp
from thrift.py3.serializer import Protocol as __Protocol
cimport thrift.py3.serializer as serializer
from thrift.py3.serializer import deserialize, serialize
import folly.iobuf as __iobuf
from folly.optional cimport cOptional

import sys
import itertools
from collections.abc import Sequence, Set, Mapping, Iterable
import warnings
import weakref as __weakref
import builtins as _builtins
cimport transitive.types as _transitive_types
import transitive.types as _transitive_types


cdef class Included(thrift.py3.types.Struct):

    def __init__(
        Included self, *,
        MyIntField=None,
        _transitive_types.Foo MyTransitiveField=None
    ):
        if MyIntField is not None:
            if not isinstance(MyIntField, int):
                raise TypeError(f'MyIntField is not a { int !r}.')
            MyIntField = <int64_t> MyIntField

        self._cpp_obj = move(Included._make_instance(
          NULL,
          NULL,
          MyIntField,
          MyTransitiveField,
        ))

    def __call__(
        Included self,
        MyIntField=__NOTSET,
        MyTransitiveField=__NOTSET
    ):
        ___NOTSET = __NOTSET  # Cheaper for larger structs
        cdef bint[2] __isNOTSET  # so make_instance is typed

        changes = False
        if MyIntField is ___NOTSET:
            __isNOTSET[0] = True
            MyIntField = None
        else:
            __isNOTSET[0] = False
            changes = True

        if MyTransitiveField is ___NOTSET:
            __isNOTSET[1] = True
            MyTransitiveField = None
        else:
            __isNOTSET[1] = False
            changes = True


        if not changes:
            return self

        if MyIntField is not None:
            if not isinstance(MyIntField, int):
                raise TypeError(f'MyIntField is not a { int !r}.')
            MyIntField = <int64_t> MyIntField

        if MyTransitiveField is not None:
            if not isinstance(MyTransitiveField, _transitive_types.Foo):
                raise TypeError(f'MyTransitiveField is not a { _transitive_types.Foo !r}.')

        inst = <Included>Included.__new__(Included)
        inst._cpp_obj = move(Included._make_instance(
          self._cpp_obj.get(),
          __isNOTSET,
          MyIntField,
          MyTransitiveField,
        ))
        return inst

    @staticmethod
    cdef unique_ptr[cIncluded] _make_instance(
        cIncluded* base_instance,
        bint* __isNOTSET,
        object MyIntField ,
        _transitive_types.Foo MyTransitiveField 
    ) except *:
        cdef unique_ptr[cIncluded] c_inst
        if base_instance:
            c_inst = make_unique[cIncluded](deref(base_instance))
        else:
            c_inst = make_unique[cIncluded]()

        if base_instance:
            # Convert None's to default value. (or unset)
            if not __isNOTSET[0] and MyIntField is None:
                deref(c_inst).MyIntField = default_inst[cIncluded]().MyIntField
                deref(c_inst).__isset.MyIntField = False
                pass

            if not __isNOTSET[1] and MyTransitiveField is None:
                deref(c_inst).MyTransitiveField = default_inst[cIncluded]().MyTransitiveField
                deref(c_inst).__isset.MyTransitiveField = False
                pass

        if MyIntField is not None:
            deref(c_inst).MyIntField = MyIntField
            deref(c_inst).__isset.MyIntField = True
        if MyTransitiveField is not None:
            deref(c_inst).MyTransitiveField = deref((<_transitive_types.Foo?> MyTransitiveField)._cpp_obj)
            deref(c_inst).__isset.MyTransitiveField = True
        # in C++ you don't have to call move(), but this doesn't translate
        # into a C++ return statement, so you do here
        return move_unique(c_inst)

    def __iter__(self):
        yield 'MyIntField', self.MyIntField
        yield 'MyTransitiveField', self.MyTransitiveField

    def __bool__(self):
        return True

    @staticmethod
    cdef create(shared_ptr[cIncluded] cpp_obj):
        inst = <Included>Included.__new__(Included)
        inst._cpp_obj = move_shared(cpp_obj)
        return inst

    @property
    def MyIntField(self):

        return deref(self._cpp_obj).MyIntField

    @property
    def MyTransitiveField(self):

        if self.__field_MyTransitiveField is None:
            self.__field_MyTransitiveField = _transitive_types.Foo.create(reference_shared_ptr_MyTransitiveField(self._cpp_obj, deref(self._cpp_obj).MyTransitiveField))
        return self.__field_MyTransitiveField


    def __hash__(Included self):
        if not self.__hash:
            self.__hash = hash((
            self.MyIntField,
            self.MyTransitiveField,
            ))
        return self.__hash

    def __repr__(Included self):
        return f'Included(MyIntField={repr(self.MyIntField)}, MyTransitiveField={repr(self.MyTransitiveField)})'
    def __copy__(Included self):
        cdef shared_ptr[cIncluded] cpp_obj = make_shared[cIncluded](
            deref(self._cpp_obj)
        )
        return Included.create(move_shared(cpp_obj))

    def __richcmp__(self, other, op):
        cdef int cop = op
        if not (
                isinstance(self, Included) and
                isinstance(other, Included)):
            if cop == Py_EQ:  # different types are never equal
                return False
            elif cop == Py_NE:  # different types are always notequal
                return True
            else:
                return NotImplemented

        cdef cIncluded* cself = (<Included>self)._cpp_obj.get()
        cdef cIncluded* cother = (<Included>other)._cpp_obj.get()
        if cop == Py_EQ:
            return deref(cself) == deref(cother)
        elif cop == Py_NE:
            return deref(cself) != deref(cother)
        elif cop == Py_LT:
            return deref(cself) < deref(cother)
        elif cop == Py_LE:
            return deref(cself) <= deref(cother)
        elif cop == Py_GT:
            return deref(cself) > deref(cother)
        elif cop == Py_GE:
            return deref(cself) >= deref(cother)
        else:
            return NotImplemented

    cdef __iobuf.IOBuf _serialize(Included self, proto):
        cdef __iobuf.cIOBufQueue queue = __iobuf.cIOBufQueue(__iobuf.cacheChainLength())
        cdef cIncluded* cpp_obj = self._cpp_obj.get()
        if proto is __Protocol.COMPACT:
            with nogil:
                serializer.CompactSerialize[cIncluded](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.BINARY:
            with nogil:
                serializer.BinarySerialize[cIncluded](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.JSON:
            with nogil:
                serializer.JSONSerialize[cIncluded](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.COMPACT_JSON:
            with nogil:
                serializer.CompactJSONSerialize[cIncluded](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        return __iobuf.from_unique_ptr(queue.move())

    cdef uint32_t _deserialize(Included self, const __iobuf.cIOBuf* buf, proto) except? 0:
        cdef uint32_t needed
        self._cpp_obj = make_shared[cIncluded]()
        cdef cIncluded* cpp_obj = self._cpp_obj.get()
        if proto is __Protocol.COMPACT:
            with nogil:
                needed = serializer.CompactDeserialize[cIncluded](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.BINARY:
            with nogil:
                needed = serializer.BinaryDeserialize[cIncluded](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.JSON:
            with nogil:
                needed = serializer.JSONDeserialize[cIncluded](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.COMPACT_JSON:
            with nogil:
                needed = serializer.CompactJSONDeserialize[cIncluded](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        return needed

    def __reduce__(self):
        return (deserialize, (Included, serialize(self)))


ExampleIncluded = Included.create(constant_shared_ptr(cExampleIncluded()))
IncludedConstant = 42
IncludedInt64 = int
TransitiveFoo = _transitive_types.Foo
