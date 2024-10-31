#include "vga.h"
#include "stdint.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "util.h"
#include "stdlib/stdio.h"
#include "keyboard.h"
#include "malloc.h"
//#include "bitter.h"
#include "multiboot.h"
#include "mem.h"

void main(uint32_t magic, struct multiboot_info* boot);

void set_screen_color(uint8_t color);

void set_screen_color(uint8_t color) {
    uint8_t* video_memory = (uint8_t*)0xC00B8000;

    for (int i = 0; i < width * height * 2; i += 2) {
        video_memory[i + 1] = color; // Set the background color byte
    }
}


void main(uint32_t magic, struct multiboot_info* boot) {
    initGdt();
    initIdt();
    initTimer();
    initKeyboard();
    print("######################\n");
    print("#        ETHOS       #\n");
    print("######################\n");
    print("ethos-->");
    set_screen_color(0x1F);

    uint32_t mod1 = *(uint32_t*)(boot->mods_addr + 4);
    uint32_t physicalAllocStart = (mod1 + 0xFFF) & ~0xFFF;

    initMemory(boot->mem_upper * 1024, physicalAllocStart);
    kmallocInit(0x1000);

    // malloc //
    //bitmap_init();
    //pmm_init();
    // paging //
    //char *ptr = (char *)0x000000001;

    //*ptr = 'a';

    //printf("%c\n", *ptr);
    for(;;);
}
