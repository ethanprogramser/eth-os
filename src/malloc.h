#ifndef MALLOC_H
#define MALLOC_H

void kmallocInit(uint32_t heapSize);
void changeHeapSize(int newSize);
void *memcpy(void *dest, const void *src, unsigned int n);
#endif
