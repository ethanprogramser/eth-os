#include "stdint.h"
#include "util.h"
#include "idt.h"
#include "vga.h"
#include "timer.h"

uint64_t ticks;
const uint32_t freq = 100;

void onIrq0(struct InterruptRegisters *regs){
    ticks += 1;
}

void initTimer(){
    ticks = 0;
    irq_install_handler(0,&onIrq0);

    //119318.16666 Mhz
    uint32_t divisor = 1193180/freq;

    //0011 0110
    outPortB(0x43,0x36);
    outPortB(0x40,(uint8_t)(divisor & 0xFF));
    outPortB(0x40,(uint8_t)((divisor >> 8) & 0xFF));
}
