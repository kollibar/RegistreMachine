#include "RM_type.hpp"


RM_type_t RM_typeOf(bool& x){return RM_BOOLEAN;};
RM_type_t RM_typeOf(int8_t& x){return RM_INTEGER8;};
RM_type_t RM_typeOf(int16_t& x){return RM_INTEGER16;};
RM_type_t RM_typeOf(int32_t& x){return RM_INTEGER32;};
RM_type_t RM_typeOf(int64_t& x){return RM_INTEGER64;};
RM_type_t RM_typeOf(uint8_t& x){return RM_UNSIGNED8;};
RM_type_t RM_typeOf(uint16_t& x){return RM_UNSIGNED16;};
RM_type_t RM_typeOf(uint32_t& x){return RM_UNSIGNED32;};
RM_type_t RM_typeOf(uint64_t& x){return RM_UNSIGNED64;};
RM_type_t RM_typeOf(float& x){return RM_REAL32;};
RM_type_t RM_typeOf(char* x){return RM_OCTET_STRING;};
//RM_type_t RM_typeOf(byte* x){return RM_DOMAIN;};
RM_type_t RM_typeOf(char& x){return RM_OCTET_STRING;};
//RM_type_t RM_typeOf(byte x){return RM_DOMAIN;};

template<typename T>
uint8_t RM_isNumeric(T x){
  RM_type_t t=RM_typeOf(x);
  return ( ( t >= 0x2 && t <= 0x8 ) || t == 0x15 || t == 0x1B);
};
template<typename T>
uint8_t RM_isNumericNotFloat(T x){
  RM_type_t t=RM_typeOf(x);
  return ( ( t >= 0x2 && t <= 0x7 ) || t == 0x15 || t == 0x1B);
};
template<typename T>
uint8_t RM_isFloat(T x){
  return ( RM_typeOf(x) == RM_REAL32 );
};
template<typename T>
uint8_t RM_isNumericSignedNotFloat(T x){
  RM_type_t t=RM_typeOf(x);
  return ( ( t >= 0x2 && t <= 0x4 ) || t == 0x15 );
};
template<typename T>
uint8_t RM_isNumericUnsignedNotFloat(T x){
  RM_type_t t=RM_typeOf(x);
  return ( ( t >= 0x5 && t <= 0x7 ) || t == 0x1B );
};
