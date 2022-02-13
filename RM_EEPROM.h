#ifndef __RM_EEPROM_H__
#define __RM_EEPROM_H__

#include <Partition.h>

#include "RM_config_default.h"
#include "RM_type.h"
#include "RM_param.h"

#include "RM_RegDesc.h"

#define RM_EEPROM_POS_INDEX 0
#define RM_EEPROM_POS_SUBINDEX 2
#define RM_EEPROM_POS_PARAM 3
#define RM_EEPROM_POS_TYPE 4
#define RM_EEPROM_POS_EEPROM_SIZE 5
#define RM_EEPROM_POS_DATA 6

#define RM_EEPROM_TAILLE_ENTETE 6

enum ERROR_EEPROM_TABLEAU_REGISTRE{
  ERREUR_OK = 0,
  ERREUR_NON_TROUVE = 0xFF,
  ERREUR_TAILLE = 0x01,
  ERREUR_PARAM = 0x02,
  ERREUR_TYPE_INCOMPATIBLE = 0x04,
  ERREUR_TYPE_DIFFERENT = 0x08,
};


typedef uint16_t EEPROMaddrReg;

class RM_EEPROM_TableauRegistre : public Partition {
public:
  RM_EEPROM_TableauRegistre(const char* nom): Partition(nom, modePartition_LectureEcriture){};

  EEPROMaddrReg get(index_t index, subindex_t subindex, void* data, size_t size, uint8_t debut, EEPROMaddrReg addr=0) const;
  EEPROMaddrReg set(index_t index, subindex_t subindex, const void* data, size_t size, uint8_t debut, EEPROMaddrReg addr=0, bool attenteActualisationCRC=false);

  EEPROMaddrReg addReg(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr=0, void* ptrRAM=NULL, size_t taille=0);
  void deleteReg(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr=0);
  void deleteReg(index_t index, subindex_t subindex, EEPROMaddrReg addr=0);

  EEPROMaddrReg actualiseStockage(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr=0);
  uint8_t checkEEPROM(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr=0) const;

  EEPROMaddrReg setDefautValue(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr=0);

protected:
  EEPROMaddrReg chercheAddr(index_t index, subindex_t subindex, EEPROMaddrReg addr = 0x0, bool pourInsertion=false) const;
  EEPROMaddrReg chercheAddr(const RM_RegDesc* regDesc PROGMEM, EEPROMaddrReg addr = 0x0, bool pourInsertion=false) const;

  bool isEnd(EEPROMaddrReg addr) const;
  EEPROMaddrReg next(EEPROMaddrReg addr) const;

  index_t getIndexAtAddr(EEPROMaddrReg addr) const;
  subindex_t getSubindexAtAddr(EEPROMaddrReg addr) const;
  RM_param_t getParamAtAddr(EEPROMaddrReg addr) const;
  RM_type_t getTypeAtAddr(EEPROMaddrReg addr) const;
  RM_size_t getSizeEEPROMDataAtAddr(EEPROMaddrReg addr) const;

  bool setIndexAtAddr(EEPROMaddrReg addr, index_t index);
  bool setSubindexAtAddr(EEPROMaddrReg addr, subindex_t subindex);
  bool setParamAtAddr(EEPROMaddrReg addr, RM_param_t param);
  bool setTypeAtAddr(EEPROMaddrReg addr, RM_type_t type);
  bool setSizeEEPROMAtAddr(EEPROMaddrReg addr, RM_size_t size);

  bool setAtAddr(EEPROMaddrReg addr, const RM_RegDesc* regDesc PROGMEM, void* ptrRAM=NULL, size_t taille=0);
  bool setDataFromRAMAtAddr(EEPROMaddrReg addr, const RM_RegDesc* regDesc PROGMEM, void* ptrRAM);
  bool setDataFromRAMAtAddr(EEPROMaddrReg addr, void* ptrRAM, size_t taille);
  bool setDataFromPGMAtAddr(EEPROMaddrReg addr, const RM_RegDesc* regDesc PROGMEM);

private:
};
#endif
