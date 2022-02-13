#include "RM_type.h"


RM_size_t RM_sizeOf(RM_type_t type){
  switch(type){
    case RM_NULL:
      return 0;
    case RM_BOOLEAN:
    case RM_INTEGER8:
    case RM_UNSIGNED8:
    case RM_Obj:  // n'est pas réellement sa taille mais met un multiple de 1
    case RM_OCTET_STRING: // pour multiple d'octet
    case RM_VISIBLE_STRING: // pour multiple d'octet
    case RM_UNICODE_STRING: // pour multiple d'octet
    case RM_DOMAIN:
      return 1;
    case RM_INTEGER16:
    case RM_UNSIGNED16:
      return 2;
    case RM_INTEGER32:
    case RM_UNSIGNED32:
    case RM_REAL32:
      return 4;
    case RM_INTEGER64:
    case RM_UNSIGNED64:
    #ifdef RM_REAL64
    case RM_REAL64:
    #endif
      return 8;

    default:
      return 0;
  }
}

uint8_t RM_type_isNull(RM_type_t type){
  return ( type == RM_NULL );
}

uint8_t RM_type_isObj(RM_type_t type){
  return ( type == RM_Obj );
}

uint8_t RM_type_isNumeric(RM_type_t type){
  #ifdef RM_REAL64
    return ( ( type >= RM_INTEGER8 && type <= RM_REAL32 ) || type == RM_INTEGER64 || type == RM_UNSIGNED64 || type == RM_REAL64 );
  #else
    return ( ( type >= RM_INTEGER8 && type <= RM_REAL32 ) || type == RM_INTEGER64 || type == RM_UNSIGNED64 );
  #endif
}
uint8_t RM_type_isNumericNotFloat(RM_type_t type){
  return ( ( type >= RM_INTEGER8 && type <= RM_UNSIGNED32 ) || type == RM_INTEGER64 || type == RM_UNSIGNED64 );
}
uint8_t RM_type_isFloat(RM_type_t type){
  #ifdef RM_REAL64
    return ( type == RM_REAL32 || type == RM_REAL64 );
  #else
    return ( type == RM_REAL32 );
  #endif
}
uint8_t RM_type_isNumericSignedNotFloat(RM_type_t type){
  return ( type == RM_INTEGER8 || type == RM_INTEGER16 || type == RM_INTEGER32 || type == RM_INTEGER64);
}
uint8_t RM_type_isNumericUnsignedNotFloat(RM_type_t type){
  return ( type == RM_UNSIGNED8 || type == RM_UNSIGNED16 || type == RM_UNSIGNED32 || type == RM_UNSIGNED64);
}
