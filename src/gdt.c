#include "gdt.h"
#include "util.h"

extern void gdt_flush(uint32_t);
extern void tss_flush();

struct gdt_entry gdt_entries[6];
struct ptr_struct ptrs;
struct tss_e tss_ent;

void init_g() {
    ptrs.limit = (sizeof(struct gdt_entry) * 6) - 1;

    ptrs.base = (uint32_t)&gdt_entries;

    set_gate(0,0,0,0,0);
    
    set_gate(1,0,0xFFFFFFFF, 0x9A, 0xCF);
    set_gate(2,0,0xFFFFFFFF, 0x92, 0xCF);
    set_gate(3,0,0xFFFFFFFF, 0xFA, 0xCF);
    set_gate(4,0,0xFFFFFFFF, 0xF2, 0xCF);

    ttsp(5,0x10, 0x0);
    gdt_flush((uint32_t)&gdt_entries);
    tss_flush();
}

void ttsp(uint32_t num, uint32_t ss0, uint32_t esp0) {
  uint32_t base = (uint32_t)&tss_ent;
  uint32_t limit = base + sizeof(tss_ent);
  set_gate(num, base, limit, 0xE9, 0x00);
  memset(&tss_ent, 0, sizeof(tss_ent));

  tss_ent.ss0 = ss0;
  tss_ent.esp0 = esp0;

  tss_ent.cs = 0x08 | 0x3;
  tss_ent.ds = tss_ent.es = tss_ent.fs = tss_ent.gs = 0x10 | 0x3;
  tss_ent.gs = 0x10 | 0x3;

}

void set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit, 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;    
}

