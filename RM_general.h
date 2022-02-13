#ifndef __RM_GENERAL_H__
#define __RM_GENERAL_H__

#include <stdint.h>

typedef uint16_t index_t;
typedef uint8_t subindex_t;

struct registre_t{
  uint16_t index;
  subindex_t subindex;
};

#endif
