#include "RM_RegDesc.h"


bool isEnd(index_t index, subindex_t subindex){
  return (index == 0xFFFF && subindex == 0xFF);
}


index_t regDescGetIndex(const RM_RegDesc* regDesc PROGMEM){
  return pgm_read_word(regDesc->index);
};
subindex_t regDescGetSubIndex(const RM_RegDesc* regDesc PROGMEM){
  return pgm_read_byte(regDesc->subindex);
}
const void* PROGMEM regDescGetFlashDataAddr(const RM_RegDesc* regDesc PROGMEM){
  return (const void*)pgm_read_word(regDesc->valeurDefaut);
};
RM_type_t regDescGetType(const RM_RegDesc* regDesc PROGMEM){
  return pgm_read_byte(regDesc->type);
}
RM_param_t regDescGetParam(const RM_RegDesc* regDesc PROGMEM){
  return pgm_read_byte(regDesc->param);
}

size_t regDescCpyFlashData(const RM_RegDesc* regDesc PROGMEM, void* data, size_t tailleMax){
  tailleMax=min(tailleMax, regDescGetSizeFlash(regDesc));

  memcpy_P(data, (const void *)pgm_read_word(regDesc->valeurDefaut), tailleMax);

  return tailleMax;
}

size_t regDescGetObjValue(const RM_RegDesc* regDesc PROGMEM, void* obj, size_t taille){
  if( taille != regDescGetSizeFlash(regDesc)) return 0;

  memcpy_P(obj, (const void*)pgm_read_word(regDesc->valeurDefaut),taille);

  return taille;
}



RM_size_t regDescGetSizeEEPROM(const RM_RegDesc* regDesc PROGMEM){
  return ( ( (regDescGetParam(regDesc)&RM_DATA_EEPROM) != 0 )?(regDescIsObj(regDesc)?pgm_read_byte(regDesc->sizeFlash):pgm_read_byte(regDesc->sizeRam)):0);
}

RM_size_t regDescGetSizeRam(const RM_RegDesc* regDesc PROGMEM){
  return ( ( (regDescGetParam(regDesc)&RM_DATA_RAM) != 0 )?pgm_read_byte(regDesc->sizeRam):0);
}
RM_size_t regDescGetSizeFlash(const RM_RegDesc* regDesc PROGMEM){
  return ( ( (regDescGetParam(regDesc)&RM_DATA_FLASH) != 0 )?pgm_read_byte(regDesc->sizeFlash):0);
}

bool regDescIsEnd(const RM_RegDesc* regDesc PROGMEM){
  return isEnd(regDescGetIndex(regDesc), regDescGetSubIndex(regDesc));
}


uint8_t regDescIsNull(const RM_RegDesc* regDesc PROGMEM){return RM_type_isNull(regDescGetType(regDesc));};
uint8_t regDescIsObj(const RM_RegDesc* regDesc PROGMEM){return RM_type_isObj(regDescGetType(regDesc));};
uint8_t regDescIsNumeric(const RM_RegDesc* regDesc PROGMEM){return RM_type_isNumeric(regDescGetType(regDesc));};
uint8_t regDescIsNumericNotFloat(const RM_RegDesc* regDesc PROGMEM){return RM_type_isNumericNotFloat(regDescGetType(regDesc));};
uint8_t regDescIsFloat(const RM_RegDesc* regDesc PROGMEM){return RM_type_isFloat(regDescGetType(regDesc));};
uint8_t regDescIsNumericSignedNotFloat(const RM_RegDesc* regDesc PROGMEM){return RM_type_isNumericSignedNotFloat(regDescGetType(regDesc));};
uint8_t regDescIsNumericUnsignedNotFloat(const RM_RegDesc* regDesc PROGMEM){return RM_type_isNumericUnsignedNotFloat(regDescGetType(regDesc));};



int8_t regDescGetInt8Value(const RM_RegDesc* regDesc PROGMEM){int8_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v));return v;}
int16_t regDescGetInt16Value(const RM_RegDesc* regDesc PROGMEM){int16_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
int32_t regDescGetInt32Value(const RM_RegDesc* regDesc PROGMEM){int32_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
int64_t regDescGetInt64Value(const RM_RegDesc* regDesc PROGMEM){int64_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
uint8_t regDescGetUint8Value(const RM_RegDesc* regDesc PROGMEM){uint8_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
uint16_t regDescGetUint16Value(const RM_RegDesc* regDesc PROGMEM){uint16_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
uint32_t regDescGetUint32Value(const RM_RegDesc* regDesc PROGMEM){uint32_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
uint64_t regDescGetUint64Value(const RM_RegDesc* regDesc PROGMEM){uint64_t v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}

bool regDescGetBoolValue(const RM_RegDesc* regDesc PROGMEM){bool v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
float regDescGetFloatValue(const RM_RegDesc* regDesc PROGMEM){float v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
#ifdef RM_ENABLE_REAL64
  float64 regDescGetBoolFloat64(const RM_RegDesc* regDesc PROGMEM){float64 v=0; memcpy_P(&v, (const void*)pgm_read_word(regDesc->valeurDefaut), sizeof(v)); return v;}
#endif







bool regDescIsWritable(const RM_RegDesc* regDesc PROGMEM){ return RM_param_isWritable(regDescGetParam(regDesc));}
bool regDescIsWritableByNetwork(const RM_RegDesc* regDesc PROGMEM){return RM_param_isWritableByNetwork(regDescGetParam(regDesc));}
bool regDescIsReadable(const RM_RegDesc* regDesc PROGMEM){return RM_param_isReadable(regDescGetParam(regDesc));}
bool regDescIsConfig(const RM_RegDesc* regDesc PROGMEM){ return RM_param_isConfig(regDescGetParam(regDesc));}

bool regDescTravailEnRam(const RM_RegDesc* regDesc PROGMEM){return RM_param_travailEnRam(regDescGetParam(regDesc));}
bool regDescTravailEnFct(const RM_RegDesc* regDesc PROGMEM){return RM_param_travailEnFct(regDescGetParam(regDesc));}
bool regDescTravailEnEEPROM(const RM_RegDesc* regDesc PROGMEM){return RM_param_travailEnEEPROM(regDescGetParam(regDesc));}
bool regDescTravailEnFlash(const RM_RegDesc* regDesc PROGMEM){return RM_param_travailEnFlash(regDescGetParam(regDesc));}

uint8_t regDescGetMediaTravail(const RM_RegDesc* regDesc PROGMEM){return RM_param_getMediaTravail(regDescGetParam(regDesc));}

bool regDescAValeurFlash(const RM_RegDesc* regDesc PROGMEM){return RM_param_aValeurFlash(regDescGetParam(regDesc));}
bool regDescAValeurEEPROM(const RM_RegDesc* regDesc PROGMEM){return RM_param_aValeurEEPROM(regDescGetParam(regDesc));}
bool regDescAValeurFct(const RM_RegDesc* regDesc PROGMEM){return RM_param_aValeurFct(regDescGetParam(regDesc));}
bool regDescAValeurRam(const RM_RegDesc* regDesc PROGMEM){return RM_param_aValeurRam(regDescGetParam(regDesc));}

bool regDescAValeurDefaut(const RM_RegDesc* regDesc PROGMEM){return RM_param_aValeurDefaut(regDescGetParam(regDesc));}
