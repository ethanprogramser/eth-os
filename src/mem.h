extern uint32_t initial_page_dir[1024];
extern int mem_num_vpages;

void initMemory(uint32_t memHigh, uint32_t physicalAllocStart);
void pmm_init(uint32_t memLow, uint32_t memHigh);
void invalidate(uint32_t vaddr);
uint32_t pmmAllocPageFrame();
uint32_t* memGetCurrentPageDir();
void memChangePageDir(uint32_t* pd);
void syncPageDirs();
void memMapPage(uint32_t virutalAddr, uint32_t physAddr, uint32_t flags);

#define KERNEL_START 0xC0000000
#define KERNEL_MALLOC 0xD000000
#define REC_PAGEDIR ((uint32_t*)0xFFFFF000)
#define REC_PAGETABLE(i) ((uint32_t*) (0xFFC00000 + ((i) << 12)))

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE (1 << 1)
#define PAGE_FLAG_OWNER (1 << 9)

