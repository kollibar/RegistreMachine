#include "RM_param.h"


uint8_t RM_param_isWritable(RM_param_t param){
  if( ( param & (RM_DATA_RAM | RM_DATA_FCT | RM_DATA_EEPROM) ) == 0 ) return 0; // si l'écriture n'est pas physiquement possible (càd uiquement FLASH)
  return ( ( param & RM_CONFIG )  == RM_CONFIG || ( param & RM_RO ) == 0 );
}
uint8_t RM_param_isReadable(RM_param_t param){
  return ( ( param & RM_CONFIG )  == RM_CONFIG || ( param & RM_WO ) == 0 );
}
uint8_t RM_param_isWritableByNetwork(RM_param_t param){
  return ( RM_param_isWritable(param) && (param & RM_WRITABLE_BY_NETWORK ) != 0 );
}

uint8_t RM_param_isConfig(RM_param_t param){
return ( ( param & RM_CONFIG )  == RM_CONFIG );
}

uint8_t RM_param_travailEnRam(RM_param_t param){
  return ( (param & RM_DATA_RAM) != 0);
}
uint8_t RM_param_travailEnFct(RM_param_t param){
  return ( (param & RM_DATA_FCT) != 0);
}
uint8_t RM_param_travailEnEEPROM(RM_param_t param){
  return ( (param & ( RM_DATA_RAM | RM_DATA_EEPROM | RM_DATA_FCT ) ) == RM_DATA_EEPROM );
}
uint8_t RM_param_travailEnFlash(RM_param_t param){
  return ( (param & ( RM_DATA_RAM | RM_DATA_EEPROM | RM_DATA_FCT | RM_DATA_FLASH) ) == RM_DATA_FLASH );
}

uint8_t RM_param_getMediaTravail(RM_param_t param){
  return ( ( param & RM_DATA_RAM )?RM_DATA_RAM:( ( param & RM_DATA_FCT )?RM_DATA_FCT:( ( param & RM_DATA_EEPROM )?RM_DATA_EEPROM:( ( param & RM_DATA_FLASH )?RM_DATA_EEPROM:0)) ) );
}

uint8_t RM_param_aValeurFlash(RM_param_t param){
  return ( (param & RM_DATA_FLASH) != 0);
}
uint8_t RM_param_aValeurEEPROM(RM_param_t param){
  return ( (param & RM_DATA_EEPROM) != 0);
}
uint8_t RM_param_aValeurFct(RM_param_t param){
  return ( (param & RM_DATA_FCT) != 0);
}
uint8_t RM_param_aValeurRam(RM_param_t param){
  return ( (param & RM_DATA_RAM) != 0);
}

uint8_t RM_param_aValeurDefaut(RM_param_t param){
  return ( (param & RM_DATA_FLASH) != 0);
}
