#ifndef __BITTER_H
#define __BITTER_H

#define BITSIZE 1024
#define ARRAY_SIZE (BITSIZE/4)

#define TOT_MEM (16 * 1024 * 1024)

#define BLOCKSIZE 4096
#define MAX (TOT_MEM / BLOCKSIZE)

uint8_t bitmap[BITSIZE];

void pmm_init();
void* pmm_alloc();
void free_pmm();

void bitmap_init();
void set_bit(int index);
void clear_bit(int index);
int check_b(int index);
int check_bit_free(int index);

void bitmap_init() {
    mem_set(bitmap, 0, ARRAY_SIZE);
}

void set_bit(int index) {
    bitmap[index/8] |= (1 << (index % 8));
}

void clear_bit(int index) {
    bitmap[index/8] &= ~(1 << (index % 8));
}

int check_b(int index) {
    return (bitmap[index/8] & (1 << (index % 8))) != 0;
}

int check_bit_free(int index) {
    for(int i=0;i<BITSIZE;i++) {
      if(!check_b(i)) {
        return i;
    }
  }
  return 0;
}

void pmm_init() {
    for(int i = 0;i<BLOCKSIZE/8;i++) {
      bitmap[i] = 0;
    }
    for(int i = 0;i<256;i++) {
        set_bit(i);
    }
}

void *pmm_alloc() {
    for(int i=0;i<MAX;i++) {
      if(!check_b(i)) {
        set_bit(i);
        return (void*)(i *BLOCKSIZE);
    }
    return 0;
  }
}

void free_pmm(void *ptr) {
    int block = (int)ptr / BLOCKSIZE;
    clear_bit(block);
}

#endif
