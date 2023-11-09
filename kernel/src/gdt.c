#include "include/gdt.h"

gdt64 gdt;
gdt64_ptr gdt_ptr;


void init_gdt() {
    gdt.gdt_null = (uint64_t)0;
    gdt.gdt_code = 0x00af9a000000ffff;
    gdt.gdt_data = 0x00cf92000000ffff;
    
    gdt_ptr.limit = sizeof(gdt64) - 1;
    gdt_ptr.base = (uint64_t)&gdt;

    asm volatile("lgdt %0" :: "m"(gdt_ptr));
}