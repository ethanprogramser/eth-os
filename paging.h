#ifndef __PAGING_H__
#define __PAGING_H__

#define PAGE_SIZE 4096
#define PAGE_T_SIZE 512

typedef struct {
  unsigned long present : 1;
  unsigned long rw : 1;
  unsigned long user : 1;
  unsigned long pwt : 1;
  unsigned long pcd : 1;
  unsigned long accessed : 1;
  unsigned long dirty : 1;
  unsigned long reserved : 1;
  uint64_t frame : 52;
}__attribute__((packed)) page_t_e;

typedef struct {
    page_t_e entry[PAGE_T_SIZE];
}__attribute__((packed)) page_t;

typedef struct {
    page_t *pml4;
}memory_manager;

void init_paging(memory_manager *mm);
#endif
