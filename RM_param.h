#ifndef __PARAMDESC_H__
#define __PARAMDESC_H__

#include "RM_config_default.h"

#include <stdint.h>

typedef uint8_t RM_param_t;

#define RM_SUBINDEX_NULL 0xFF
#define RM_SUBINDEX_INDEXONLY 0xFE


#define RM_BITS_TYPE_DATA    0b00001111
#define RM_DATA_FLASH        0b00001000
#define RM_DATA_RAM          0b00000001
#define RM_DATA_FCT          0b00000010
#define RM_DATA_EEPROM       0b00000100

#define RM_PARAM_NULL        0b00000000

#define RM_WRITABLE_BY_NETWORK        0b00100000  //peut être écrit par le réseau (CAN, modbus, ...)
#define RM_RO                         0b10000000  // EST read-only
#define RM_WO                         0b01000000  // EST write-only
#define RM_RW                         0           // readable et writable (càd non read-only ni write-only)
#define RM_CONFIG                     0b11000000  // variable de config, donc readable et writable malgré les bits read-only et write-only ! pour traitement spécifique config
#define RM_CONFIG_VAL_DEFAUT_PROGMEM  (RM_CONFIG | RM_DATA_FLASH) // config et a une valeur par defaut en flash
#define RM_STORAGE_EEPROM_VOLATILE    0b00010000  // ??????

#define RM_BITS_READ_WRITE    0b11000000  // masque pour les bits read/write/config


uint8_t RM_param_isWritable(RM_param_t param);
uint8_t RM_param_isReadable(RM_param_t param);
uint8_t RM_param_isWritableByNetwork(RM_param_t param);
uint8_t RM_param_isConfig(RM_param_t param);


uint8_t RM_param_travailEnRam(RM_param_t param);
uint8_t RM_param_travailEnFct(RM_param_t param);
uint8_t RM_param_travailEnEEPROM(RM_param_t param);
uint8_t RM_param_travailEnFlash(RM_param_t param);

uint8_t RM_param_getMediaTravail(RM_param_t param);

uint8_t RM_param_aValeurFlash(RM_param_t param);
uint8_t RM_param_aValeurEEPROM(RM_param_t param);
uint8_t RM_param_aValeurFct(RM_param_t param);
uint8_t RM_param_aValeurRam(RM_param_t param);

uint8_t RM_param_aValeurDefaut(RM_param_t param);


#endif
