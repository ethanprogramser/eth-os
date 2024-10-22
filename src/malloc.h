#ifndef MALLOC_H
#define MALLOC_H

#include "stdint.h"

void mem_copy(uint8_t *src, uint8_t *des, int bytes);
void mem_set(uint8_t *dest, uint8_t val, uint32_t len);

uint32_t ethoc(uint32_t size, int align, uint32_t *paddr);

#endif
