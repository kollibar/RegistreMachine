#ifndef __RM_REGISTRE_H__
#define __RM_REGISTRE_H__

#include "RM_config_default.h"
#include "RM_RegDesc.h"
#include "RM_type.hpp"


enum RM_Registre_ERROR{
  ERROR_OK=0,
  ERROR_NEED_ALLOCATION,
  ERROR_NO_MORE_MEMORY,
  ERROR_FCT_NULL,
  ERROR_NO_REGISTRE_ADDRESS,
  ERROR_ACTION_NON_SUPPORTE,
  ERROR_ADDRESS_REGISTRE_NON_VALIDE,
  ERROR_NO_NEXT_IN_VOLATILE,
  ERROR_CRC_EEPROM,
  ERROR_END,
  ERROR_PTR_DATA_NULL,
  ERROR_REGISTRE_NON_INITIALIZED,
  ERROR_NO_PGM_VALUE,
  ERROR_EEPROM_ADDRESS_OUT_OF_SIZE,
  ERROR_NO_DATA_TO_SAVE,
  ERROR_NO_PLACE_TO_LOAD_DATA,
  ERROR_TAILLE_DIFFERENTE,
  EEROR_EEPROM_NON_INITIALISE,
  ERROR_VARIABLE_NON_EEPROM,
  ERROR_VARIABLE_NON_TROUVE_EEPROM,
};
typedef enum RM_Registre_ERROR RM_Registre_ERROR;


class RM_Registre{
  //friend class RM_TableauRegistre;
public:
  RM_Registre();
  RM_Registre(RM_RegDesc * regDesc PROGMEM);

  void setNull();
  bool setPtrRAM(void* data);
  bool setPtrEEPROM(void* data);

  index_t getIndex() const;
  subindex_t getSubindex() const;
  RM_type_t getType() const;
  RM_param_t getParam() const;
  const void* PROGMEM getAddrFlashData() const;

  template<typename T>
  T getDefaultValue() const;
  template<typename T>
  size_t getDefaultValue(T* data) const;
  template<typename T>
  bool isTypeOf(T) const;

  bool isObj() const;
  uint8_t isNull() const;
  uint8_t isNumeric() const;
  uint8_t isNumericNotFloat() const;
  uint8_t isFloat() const;
  uint8_t isNumericSignedNotFloat() const;
  uint8_t isNumericUnsignedNotFloat() const;

  RM_size_t getSizeRam() const;
  RM_size_t getSizeFlash() const;
  RM_size_t getSizeEEPROM() const;

  bool travailEnRam() const{return regDescTravailEnRam(this->descr);};
  bool travailEnFct() const{return regDescTravailEnFct(this->descr);};
  bool travailEnEEPROM() const{return regDescTravailEnEEPROM(this->descr);};
  bool travailEnFlash() const{return regDescTravailEnFlash(this->descr);};

  uint8_t getMediaTravail() const{return regDescGetMediaTravail(this->descr);};

  bool aValeurFlash() const{return regDescAValeurFlash(this->descr);};
  bool aValeurEEPROM() const{return regDescAValeurEEPROM(this->descr);};
  bool aValeurFct() const{return regDescAValeurFct(this->descr);};
  bool aValeurRam() const{return regDescAValeurRam(this->descr);};

  bool aValeurDefaut() const{return regDescAValeurDefaut(this->descr);};

  bool isWritable() const{ return regDescIsWritable(this->descr);}
  bool isWritableByNetwork() const{return regDescIsWritableByNetwork(this->descr);};
  bool isReadable() const{return regDescIsReadable(this->descr);};
  bool isConfig() const{ return regDescIsConfig(this->descr);};

  bool isEnd() const{return regDescIsEnd(this->descr);};

  bool next();


  size_t set(void* data, size_t size, uint8_t debut);
  size_t get(void* data, size_t size, uint8_t debut);

  void* getPtrData() const;

  RM_Registre_ERROR sendDataRamToFct();
  RM_Registre_ERROR sendDataRamToEEPROM();
  RM_Registre_ERROR sendDataEEPROMToFct();
  RM_Registre_ERROR sendDataEEPROMToRam();
  RM_Registre_ERROR sendDataPGMToRam();
  RM_Registre_ERROR sendDataPGMToFct();
  RM_Registre_ERROR sendDataPGMToEEPROM();
  RM_Registre_ERROR sendDataFctToEEPROM();
  RM_Registre_ERROR sendDataFctToRAM();

  RM_Registre_ERROR chargeValeurEEPROM();
  RM_Registre_ERROR chargeValeurFlash();

  RM_Registre_ERROR chargeValeurDefaut();
  RM_Registre_ERROR chargeValeurDemarrage();

  RM_Registre_ERROR sauveValeur();

  RM_Registre_ERROR effaceDataRAM();
  RM_Registre_ERROR effaceDataEEPROM();
  RM_Registre_ERROR effaceDataFct();

private:
  void* ptrRAM;
  void* ptrEEPROM;
  RM_RegDesc* descr PROGMEM;
};

/*

typedef struct RM_Registre RM_Registre;
struct RM_Registre{
  void* ptrRAM;
  void* ptrEEPROM;
  RM_RegDesc* descr PROGMEM;
};

inline index_t registreGetIndex(RM_Registre registre){return regDescGetIndex(registre.descr);};
inline subindex_t registreGetSubIndex(RM_Registre registre){return regDescGetSubIndex(registre.descr);};
inline const void* PROGMEM registreGetFlashData(RM_Registre registre){return regDescGetFlashDataAddr(registre.descr);};
inline RM_type_t registreGetType(RM_Registre registre){return regDescGetType(registre.descr);};
inline RM_param_t registreGetParam(RM_Registre registre){return regDescGetParam(registre.descr);};

inline bool registreIsObj(RM_Registre registre){return regDescIsObj(registre.descr);};
inline uint8_t registreIsNull(RM_Registre registre){return regDescIsNull(registre.descr);};
inline uint8_t registreIsNumeric(RM_Registre registre){return regDescIsNumeric(registre.descr);};
inline uint8_t registreIsNumericNotFloat(RM_Registre registre){return regDescIsNumericNotFloat(registre.descr);};
inline uint8_t registreIsFloat(RM_Registre registre){return regDescIsFloat(registre.descr);};
inline uint8_t registreIsNumericSignedNotFloat(RM_Registre registre){return regDescIsNumericSignedNotFloat(registre.descr);};
inline uint8_t registreIsNumericUnsignedNotFloat(RM_Registre registre){return regDescIsNumericUnsignedNotFloat(registre.descr);};

inline RM_size_t registreGetSizeRam(RM_Registre registre){return regDescGetSizeRam(registre.descr);};
inline RM_size_t registreGetSizeFlash(RM_Registre registre){return regDescGetSizeFlash(registre.descr);};
inline RM_size_t registreGetSizeEEPROM(RM_Registre registre){return regDescGetSizeEEPROM(registre.descr);};

inline int8_t registreGetInt8Value(RM_Registre registre){return regDescGetInt8Value(registre.descr);};
inline int16_t registreGetInt16Value(RM_Registre registre){return regDescGetInt16Value(registre.descr);};
inline int32_t registreGetInt32Value(RM_Registre registre){return regDescGetInt32Value(registre.descr);};
inline int64_t registreGetInt64Value(RM_Registre registre){return regDescGetInt64Value(registre.descr);};
inline uint8_t registreGetUint8Value(RM_Registre registre){return regDescGetUint8Value(registre.descr);};
inline uint16_t registreGetUint16Value(RM_Registre registre){return regDescGetUint16Value(registre.descr);};
inline uint32_t registreGetUint32Value(RM_Registre registre){return regDescGetUint32Value(registre.descr);};
inline uint64_t registreGetUint64Value(RM_Registre registre){return regDescGetUint64Value(registre.descr);};

inline bool registreGetBoolValue(RM_Registre registre){return regDescGetBoolValue(registre.descr);};
inline float registreGetFloatValue(RM_Registre registre){return regDescGetFloatValue(registre.descr);};
#ifdef RM_ENABLE_REAL64
  inline float64 getFloat64Value(RM_Registre registre){return regDescGetFloat64Value(registre.descr);};
#endif


inline bool registreTravailEnRam(RM_Registre registre){return regDescTravailEnRam(registre.descr);};
inline bool registreTravailEnFct(RM_Registre registre){return regDescTravailEnFct(registre.descr);};
inline bool registreTravailEnEEPROM(RM_Registre registre){return regDescTravailEnEEPROM(registre.descr);};
inline bool registreTravailEnFlash(RM_Registre registre){return regDescTravailEnFlash(registre.descr);};

inline uint8_t registreGetMediaTravail(RM_Registre registre){return regDescGetMediaTravail(registre.descr);};

inline bool registreAValeurFlash(RM_Registre registre){return regDescAValeurFlash(registre.descr);};
inline bool registreAValeurEEPROM(RM_Registre registre){return regDescAValeurEEPROM(registre.descr);};
inline bool registreAValeurFct(RM_Registre registre){return regDescAValeurFct(registre.descr);};
inline bool registreAValeurRam(RM_Registre registre){return regDescAValeurRam(registre.descr);};

inline bool registreAValeurDefaut(RM_Registre registre){return regDescAValeurDefaut(registre.descr);};

inline bool registreIsWritable(RM_Registre registre){ return regDescIsWritable(registre.descr);}
inline bool registreIsWritableByNetwork(RM_Registre registre){return regDescIsWritableByNetwork(registre.descr);};
inline bool registreIsReadable(RM_Registre registre){return regDescIsReadable(registre.descr);};
inline bool registreIsConfig(RM_Registre registre){ return regDescIsConfig(registre.descr);};

inline bool registreIsEnd(RM_Registre registre){return regDescIsEnd(registre.descr);};

size_t registreSet(RM_Registre registre, void* data, size_t size, uint8_t debut);
size_t registreGet(RM_Registre registre, void* data, size_t size, uint8_t debut);

void* registreGetPtrData(RM_Registre registre);

RM_Registre_ERROR registreSendDataRamToFct(RM_Registre registre);
RM_Registre_ERROR registreSendDataRamToEEPROM(RM_Registre registre);
RM_Registre_ERROR registreSendDataEEPROMToFct(RM_Registre registre);
RM_Registre_ERROR registreSendDataEEPROMToRam(RM_Registre registre);
RM_Registre_ERROR registreSendDataPGMToRam(RM_Registre registre);
RM_Registre_ERROR registreSendDataPGMToFct(RM_Registre registre);
RM_Registre_ERROR registreSendDataPGMToEEPROM(RM_Registre registre);
RM_Registre_ERROR registreSendDataFctToEEPROM(RM_Registre registre);
RM_Registre_ERROR registreSendDataFctToRAM(RM_Registre registre);

RM_Registre_ERROR registreChargeValeurEEPROM(RM_Registre registre);
RM_Registre_ERROR registreChargeValeurFlash(RM_Registre registre);

RM_Registre_ERROR registreChargeValeurDefaut(RM_Registre registre);
RM_Registre_ERROR registreChargeValeurDemarrage(RM_Registre registre);

RM_Registre_ERROR registreSauveValeur(RM_Registre registre);

RM_Registre_ERROR registreEffaceDataRAM(RM_Registre registre);
RM_Registre_ERROR registreEffaceDataEEPROM(RM_Registre registre);
RM_Registre_ERROR registreEffaceDataFct(RM_Registre registre);
*/
#endif
