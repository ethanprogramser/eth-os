#include "stdint.h"
#include "util.h"
#include "mem.h"
#include "malloc.h"

static uint32_t heapStart;
static uint32_t heapSize;
static uint32_t threshold;
static bool kmallocInitalized = false;

void kmallocInit(uint32_t initialHeapSize){
    heapStart = KERNEL_MALLOC;
    heapSize = 0;
    threshold = 0;
    kmallocInitalized = true;

    changeHeapSize(initialHeapSize);
    *((uint32_t*)heapStart) = 0;
}

void changeHeapSize(int newSize){
    int oldPageTop = CEIL_DIV(heapSize, 0x1000);
    int newPageTop = CEIL_DIV(newSize, 0x1000);

    if (newPageTop > oldPageTop){
        int diff = newPageTop - oldPageTop;

        for (int i = 0; i < diff; i++){
            uint32_t phys = pmmAllocPageFrame();
            memMapPage(KERNEL_MALLOC + oldPageTop * 0x1000 + i * 0x1000, phys, PAGE_FLAG_WRITE);
        }
    }

    heapSize = newSize;
}



