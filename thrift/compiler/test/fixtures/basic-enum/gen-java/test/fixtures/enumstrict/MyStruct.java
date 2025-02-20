/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package test.fixtures.enumstrict;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Collections;
import java.util.BitSet;
import java.util.Arrays;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.facebook.thrift.*;
import com.facebook.thrift.async.*;
import com.facebook.thrift.meta_data.*;
import com.facebook.thrift.server.*;
import com.facebook.thrift.transport.*;
import com.facebook.thrift.protocol.*;

@SuppressWarnings({ "unused", "serial" })
public class MyStruct implements TBase, java.io.Serializable, Cloneable, Comparable<MyStruct> {
  private static final TStruct STRUCT_DESC = new TStruct("MyStruct");
  private static final TField MY_ENUM_FIELD_DESC = new TField("myEnum", TType.I32, (short)1);
  private static final TField MY_BIG_ENUM_FIELD_DESC = new TField("myBigEnum", TType.I32, (short)2);

  /**
   * 
   * @see MyEnum
   */
  public MyEnum myEnum;
  /**
   * 
   * @see MyBigEnum
   */
  public MyBigEnum myBigEnum;
  public static final int MYENUM = 1;
  public static final int MYBIGENUM = 2;
  public static boolean DEFAULT_PRETTY_PRINT = true;

  // isset id assignments
  private static final int __MYENUM_ISSET_ID = 0;
  private static final int __MYBIGENUM_ISSET_ID = 1;
  private BitSet __isset_bit_vector = new BitSet(2);

  public static final Map<Integer, FieldMetaData> metaDataMap;
  static {
    Map<Integer, FieldMetaData> tmpMetaDataMap = new HashMap<Integer, FieldMetaData>();
    tmpMetaDataMap.put(MYENUM, new FieldMetaData("myEnum", TFieldRequirementType.DEFAULT, 
        new FieldValueMetaData(TType.I32)));
    tmpMetaDataMap.put(MYBIGENUM, new FieldMetaData("myBigEnum", TFieldRequirementType.DEFAULT, 
        new FieldValueMetaData(TType.I32)));
    metaDataMap = Collections.unmodifiableMap(tmpMetaDataMap);
  }

  static {
    FieldMetaData.addStructMetaDataMap(MyStruct.class, metaDataMap);
  }

  public MyStruct() {
    this.myBigEnum = test.fixtures.enumstrict.MyBigEnum.ONE;

  }

  public MyStruct(
    MyEnum myEnum,
    MyBigEnum myBigEnum)
  {
    this();
    this.myEnum = myEnum;
    setMyEnumIsSet(true);
    this.myBigEnum = myBigEnum;
    setMyBigEnumIsSet(true);
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public MyStruct(MyStruct other) {
    __isset_bit_vector.clear();
    __isset_bit_vector.or(other.__isset_bit_vector);
    this.myEnum = TBaseHelper.deepCopy(other.myEnum);
    this.myBigEnum = TBaseHelper.deepCopy(other.myBigEnum);
  }

  public MyStruct deepCopy() {
    return new MyStruct(this);
  }

  @Deprecated
  public MyStruct clone() {
    return new MyStruct(this);
  }

  /**
   * 
   * @see MyEnum
   */
  public MyEnum getMyEnum() {
    return this.myEnum;
  }

  /**
   * 
   * @see MyEnum
   */
  public MyStruct setMyEnum(MyEnum myEnum) {
    this.myEnum = myEnum;
    setMyEnumIsSet(true);
    return this;
  }

  public void unsetMyEnum() {
    __isset_bit_vector.clear(__MYENUM_ISSET_ID);
  }

  // Returns true if field myEnum is set (has been assigned a value) and false otherwise
  public boolean isSetMyEnum() {
    return __isset_bit_vector.get(__MYENUM_ISSET_ID);
  }

  public void setMyEnumIsSet(boolean value) {
    __isset_bit_vector.set(__MYENUM_ISSET_ID, value);
  }

  /**
   * 
   * @see MyBigEnum
   */
  public MyBigEnum getMyBigEnum() {
    return this.myBigEnum;
  }

  /**
   * 
   * @see MyBigEnum
   */
  public MyStruct setMyBigEnum(MyBigEnum myBigEnum) {
    this.myBigEnum = myBigEnum;
    setMyBigEnumIsSet(true);
    return this;
  }

  public void unsetMyBigEnum() {
    __isset_bit_vector.clear(__MYBIGENUM_ISSET_ID);
  }

  // Returns true if field myBigEnum is set (has been assigned a value) and false otherwise
  public boolean isSetMyBigEnum() {
    return __isset_bit_vector.get(__MYBIGENUM_ISSET_ID);
  }

  public void setMyBigEnumIsSet(boolean value) {
    __isset_bit_vector.set(__MYBIGENUM_ISSET_ID, value);
  }

  public void setFieldValue(int fieldID, Object value) {
    switch (fieldID) {
    case MYENUM:
      if (value == null) {
        unsetMyEnum();
      } else {
        setMyEnum((MyEnum)value);
      }
      break;

    case MYBIGENUM:
      if (value == null) {
        unsetMyBigEnum();
      } else {
        setMyBigEnum((MyBigEnum)value);
      }
      break;

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  public Object getFieldValue(int fieldID) {
    switch (fieldID) {
    case MYENUM:
      return getMyEnum();

    case MYBIGENUM:
      return getMyBigEnum();

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  // Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise
  public boolean isSet(int fieldID) {
    switch (fieldID) {
    case MYENUM:
      return isSetMyEnum();
    case MYBIGENUM:
      return isSetMyBigEnum();
    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof MyStruct)
      return this.equals((MyStruct)that);
    return false;
  }

  public boolean equals(MyStruct that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_myEnum = true;
    boolean that_present_myEnum = true;
    if (this_present_myEnum || that_present_myEnum) {
      if (!(this_present_myEnum && that_present_myEnum))
        return false;
      if (!TBaseHelper.equalsNobinary(this.myEnum, that.myEnum))
        return false;
    }

    boolean this_present_myBigEnum = true;
    boolean that_present_myBigEnum = true;
    if (this_present_myBigEnum || that_present_myBigEnum) {
      if (!(this_present_myBigEnum && that_present_myBigEnum))
        return false;
      if (!TBaseHelper.equalsNobinary(this.myBigEnum, that.myBigEnum))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  @Override
  public int compareTo(MyStruct other) {
    if (other == null) {
      // See java.lang.Comparable docs
      throw new NullPointerException();
    }

    if (other == this) {
      return 0;
    }
    int lastComparison = 0;

    lastComparison = Boolean.valueOf(isSetMyEnum()).compareTo(other.isSetMyEnum());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(myEnum, other.myEnum);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetMyBigEnum()).compareTo(other.isSetMyBigEnum());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(myBigEnum, other.myBigEnum);
    if (lastComparison != 0) {
      return lastComparison;
    }
    return 0;
  }

  public void read(TProtocol iprot) throws TException {
    TField field;
    iprot.readStructBegin(metaDataMap);
    while (true)
    {
      field = iprot.readFieldBegin();
      if (field.type == TType.STOP) { 
        break;
      }
      switch (field.id)
      {
        case MYENUM:
          if (field.type == TType.I32) {
            this.myEnum = MyEnum.findByValue(iprot.readI32());
            setMyEnumIsSet(true);
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case MYBIGENUM:
          if (field.type == TType.I32) {
            this.myBigEnum = MyBigEnum.findByValue(iprot.readI32());
            setMyBigEnumIsSet(true);
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        default:
          TProtocolUtil.skip(iprot, field.type);
          break;
      }
      iprot.readFieldEnd();
    }
    iprot.readStructEnd();


    // check for required fields of primitive type, which can't be checked in the validate method
    validate();
  }

  public void write(TProtocol oprot) throws TException {
    validate();

    oprot.writeStructBegin(STRUCT_DESC);
    oprot.writeFieldBegin(MY_ENUM_FIELD_DESC);
    oprot.writeI32(this.myEnum == null ? 0 : this.myEnum.getValue());
    oprot.writeFieldEnd();
    oprot.writeFieldBegin(MY_BIG_ENUM_FIELD_DESC);
    oprot.writeI32(this.myBigEnum == null ? 0 : this.myBigEnum.getValue());
    oprot.writeFieldEnd();
    oprot.writeFieldStop();
    oprot.writeStructEnd();
  }

  @Override
  public String toString() {
    return toString(DEFAULT_PRETTY_PRINT);
  }

  @Override
  public String toString(boolean prettyPrint) {
    return toString(1, prettyPrint);
  }

  @Override
  public String toString(int indent, boolean prettyPrint) {
    String indentStr = prettyPrint ? TBaseHelper.getIndentedString(indent) : "";
    String newLine = prettyPrint ? "\n" : "";
    String space = prettyPrint ? " " : "";
    StringBuilder sb = new StringBuilder("MyStruct");
    sb.append(space);
    sb.append("(");
    sb.append(newLine);
    boolean first = true;

    sb.append(indentStr);
    sb.append("myEnum");
    sb.append(space);
    sb.append(":").append(space);
    String myEnum_name = MyEnum.VALUES_TO_NAMES.get(this.getMyEnum());
    if (myEnum_name != null) {
      sb.append(myEnum_name);
      sb.append(" (");
    }
    sb.append(this.getMyEnum());
    if (myEnum_name != null) {
      sb.append(")");
    }
    first = false;
    if (!first) sb.append("," + newLine);
    sb.append(indentStr);
    sb.append("myBigEnum");
    sb.append(space);
    sb.append(":").append(space);
    String myBigEnum_name = MyBigEnum.VALUES_TO_NAMES.get(this.getMyBigEnum());
    if (myBigEnum_name != null) {
      sb.append(myBigEnum_name);
      sb.append(" (");
    }
    sb.append(this.getMyBigEnum());
    if (myBigEnum_name != null) {
      sb.append(")");
    }
    first = false;
    sb.append(newLine + TBaseHelper.reduceIndent(indentStr));
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws TException {
    // check for required fields
  }

}

