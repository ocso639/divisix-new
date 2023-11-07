#include "include/idt.h"
#include "include/video.h"
#include "include/assembly.h"
#include "include/string.h"
#include "include/exceptions.h"

idt idt_entries[256];
idtr idt_pointer;

void set_idt(int index, uint64_t base, uint8_t flags) {
    idt_entries[index].offset_low = (base & 0xFFFF);
    idt_entries[index].offset_middle = (base >> 16) & 0xFFFF;
    idt_entries[index].offset_high = (base >> 32) & 0xFFFFFFFF;
    idt_entries[index].selector = 0x8;
    idt_entries[index].ist = 0;
    idt_entries[index].flags = flags;
    idt_entries[index].zero = 0;
}

/*extern void c_divide_zero(interrupt_frame* iframe) {
    kfails("Divide by zero caught!\n");
    kputs(itoa(iframe->r10, 16));
}

extern void c_debug(uintptr_t* stack) {
    kfails("Debug exception\n");
    for (int i = 0; i < 23; i++) {
        kputs(itoa((uintptr_t)stack[i], 16));
        kputs("\n");
    }
    //ireturn;
}

extern void c_nmi(interrupt_frame* iframe) {
    kinfos("Non Maskable interrupt\n");
    kputs(itoa(iframe->r10, 16));
}

extern void c_breakpoint(interrupt_frame* iframe) {
    kinfos("Breakpoint\n");
    kputs(itoa(iframe->r10, 16));
}

extern void c_overflow(interrupt_frame* iframe) {
    kfails("Overflow!\n");
    kputs(itoa(iframe->r10, 16));
}

extern void c_boundrange(interrupt_frame* iframe) {
    kfails("Boundrange\n");
    kputs(itoa(iframe->r10, 16));
} 

extern void c_invalid_op(interrupt_frame* iframe) {
    kfails("Invalid Opcode!\n");
    kputs(itoa(iframe->r10, 16));
}

extern void c_device_unavail(interrupt_frame* iframe) {
    kfails("General Protection Fault\n");
    hcf();
}

extern void c_double_fault(uintptr_t* stack) {
    kfails("Double Fault, restart your computer now.\n");
    for (int i = 0; i < 23; i++) {
        kputs(itoa((uintptr_t)stack[i], 16));
        kputs("\n");
    }
    hcf();
}
*/

extern void c_divide_zero() {
    koops("Division by zero\n");
}

extern void c_debug() {
    kinfos("Debug exception\n");
}

extern void c_double_fault() {
    kpanic("Double fault while handling exception\n");
    hcf();
}

void idt_init() {
    idt_pointer.limit = (sizeof(idt) * 256) - 1;
    idt_pointer.base = (uint64_t)&idt_entries;
    
    //set_idt(0x0, (uint64_t)division_by_zero, 0x8E);
    set_idt(0x0, (uint64_t)divide_zero, 0x8E);
    set_idt(0x1, (uint64_t)debug, 0x8E);
    set_idt(0x8, (uint64_t)double_fault, 0x8E);

    asm volatile("lidt %0" :: "m"(idt_pointer));
    asm volatile("sti");
} 