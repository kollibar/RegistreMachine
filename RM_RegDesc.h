#ifndef __RM_REGDESC_H__
#define __RM_REGDESC_H__

#include <Arduino_FreeRTOS.h>
#include <Arduino.h>

#include "RM_config_default.h"
#include "RM_type.h"
#include "RM_param.h"

/**
 * \class struct
 * \brief Objet regDesc: description de variable
 *
 * RM_RegDesc est un objet contenant la description d'un registre
 */

typedef struct RM_RegDesc RM_RegDesc;
struct RM_RegDesc{
  index_t index;  /*!< index du registre */
  subindex_t subindex;   /*!< subindex du registre */
  RM_param_t param;   /*!< paramètres du registre */
  RM_type_t type;  /*!< type de la variable stocké dans le registre  (voir RM.type.h) */
  RM_size_t sizeRam;   /*!< taille en RAM de la variable */
  RM_size_t sizeFlash;  /*!< taille en Flash de la variable */
  const char* PROGMEM valeurDefaut; /*!< pointeur vers une valeur par défaut en flash. Null si pas de valeur par défaut */
};

bool isEnd(index_t index, subindex_t subindex);

index_t regDescGetIndex(const RM_RegDesc* regDesc PROGMEM);
subindex_t regDescGetSubIndex(const RM_RegDesc* regDesc PROGMEM);
const void* PROGMEM regDescGetFlashDataAddr(const RM_RegDesc* regDesc PROGMEM);
RM_type_t regDescGetType(const RM_RegDesc* regDesc PROGMEM);
RM_param_t regDescGetParam(const RM_RegDesc* regDesc PROGMEM);

size_t regDescCpyFlashData(const RM_RegDesc* regDesc PROGMEM, char* data, size_t tailleMax);

bool regDescIsEnd(const RM_RegDesc* regDesc PROGMEM);

uint8_t regDescIsNull(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescIsObj(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescIsNumeric(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescIsNumericNotFloat(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescIsFloat(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescIsNumericSignedNotFloat(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescIsNumericUnsignedNotFloat(const RM_RegDesc* regDesc PROGMEM);

RM_size_t regDescGetSizeEEPROM(const RM_RegDesc* regDesc PROGMEM);
RM_size_t regDescGetSizeRam(const RM_RegDesc* regDesc PROGMEM);
RM_size_t regDescGetSizeFlash(const RM_RegDesc* regDesc PROGMEM);



int8_t regDescGetInt8Value(const RM_RegDesc* regDesc PROGMEM);
int16_t regDescGetInt16Value(const RM_RegDesc* regDesc PROGMEM);
int32_t regDescGetInt32Value(const RM_RegDesc* regDesc PROGMEM);
int64_t regDescGetInt64Value(const RM_RegDesc* regDesc PROGMEM);
uint8_t regDescGetUint8Value(const RM_RegDesc* regDesc PROGMEM);
uint16_t regDescGetUint16Value(const RM_RegDesc* regDesc PROGMEM);
uint32_t regDescGetUint32Value(const RM_RegDesc* regDesc PROGMEM);
uint64_t regDescGetUint64Value(const RM_RegDesc* regDesc PROGMEM);

bool regDescGetBoolValue(const RM_RegDesc* regDesc PROGMEM);
float regDescGetFloatValue(const RM_RegDesc* regDesc PROGMEM);
#ifdef RM_ENABLE_REAL64
  float64 regDescGetBoolFloat64(const RM_RegDesc* regDesc PROGMEM);
#endif

size_t regDescGetObjValue(const RM_RegDesc* regDesc PROGMEM, void* obj, size_t taille);


bool regDescIsWritable(const RM_RegDesc* regDesc PROGMEM);
bool regDescIsWritableByNetwork(const RM_RegDesc* regDesc PROGMEM);
bool regDescIsReadable(const RM_RegDesc* regDesc PROGMEM);
bool regDescIsConfig(const RM_RegDesc* regDesc PROGMEM);

bool regDescTravailEnRam(const RM_RegDesc* regDesc PROGMEM);
bool regDescTravailEnFct(const RM_RegDesc* regDesc PROGMEM);
bool regDescTravailEnEEPROM(const RM_RegDesc* regDesc PROGMEM);
bool regDescTravailEnFlash(const RM_RegDesc* regDesc PROGMEM);

uint8_t regDescGetMediaTravail(const RM_RegDesc* regDesc PROGMEM);

bool regDescAValeurFlash(const RM_RegDesc* regDesc PROGMEM);
bool regDescAValeurEEPROM(const RM_RegDesc* regDesc PROGMEM);
bool regDescAValeurFct(const RM_RegDesc* regDesc PROGMEM);
bool regDescAValeurRam(const RM_RegDesc* regDesc PROGMEM);

bool regDescAValeurDefaut(const RM_RegDesc* regDesc PROGMEM);

#endif
