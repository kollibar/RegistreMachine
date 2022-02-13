#ifndef __CANINOSDATA_TYPE_H__
#define __CANINOSDATA_TYPE_H__

#include "RM_config_default.h"

#include <stdint.h>


typedef uint8_t RM_type_t;
typedef uint8_t RM_size_t;


#define RM_NULL            0
#define RM_BOOLEAN         0x1
#define RM_INTEGER8        0x2
#define RM_INTEGER16       0x3
#define RM_INTEGER32       0x4
#define RM_UNSIGNED8       0x5
#define RM_UNSIGNED16      0x6
#define RM_UNSIGNED32      0x7
#define RM_REAL32          0x8
#define RM_VISIBLE_STRING  0x9
#define RM_OCTET_STRING    0xA
#define RM_UNICODE_STRING  0xB
#define RM_DOMAIN          0xF
#ifdef RM_ENABLE_REAL64
  #define RM_REAL64        0x11
#endif
#define RM_INTEGER64       0x15
#define RM_UNSIGNED64      0x1B
#define RM_Obj         0b10000000

#define RM_STRING  RM_OCTET_STRING
#define RM_CHAR    RM_UNSIGNED8


uint8_t RM_type_isNull(RM_type_t type);
uint8_t RM_type_isObj(RM_type_t type);
uint8_t RM_type_isNumeric(RM_type_t type);
uint8_t RM_type_isNumericNotFloat(RM_type_t type);
uint8_t RM_type_isFloat(RM_type_t type);
uint8_t RM_type_isNumericSignedNotFloat(RM_type_t type);
uint8_t RM_type_isNumericUnsignedNotFloat(RM_type_t type);



RM_size_t RM_sizeOf(RM_type_t type);

#endif
