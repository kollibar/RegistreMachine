#ifndef __RM_TABLEAUREGISTRE_H__
#define __RM_TABLEAUREGISTRE_H__

#include <Arduino_FreeRTOS.h>

#include "RM_config_default.h"
#include "RM_Registre.h"


class RM_TableauRegistre{
public:
  RM_TableauRegistre();

  RM_Registre getRegistre(index_t index, subindex_t subindex);
  size_t getSizeRAM();
  size_t getSizeEEPROM();
  size_t mallocRAM();
  void freeRAM();
  void setRAM(void* ptr, size_t tailleRAM=0xFFFF);

  void chargeValeurDemarrage();
  void chargeValeurDefaut();
private:
  void* ptrRAM;
  void* ptrEEPROM;
  RM_RegDesc* descrRegistre0 PROGMEM;
};

#endif
