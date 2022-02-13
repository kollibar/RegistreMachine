#ifndef __RM_MODBUS_TRANSLATOR_H__
#define __RM_MODBUS_TRANSLATOR_H__

#include "RM_config_default.h"

struct ModBusTranslator{
  uint16_t modbus;

  index_t index;
  subindex_t subindex;
};



#endif
