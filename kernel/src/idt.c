#include "include/video.h"
#include "arch/x86_64/include/idt.h"
#include "arch/x86_64/include/assembly.h"
#include "arch/x86_64/include/exceptions.h"
#include "include/string.h"

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

/*extern void c_divide_zero(uintptr_t* iframe) {
    kfails("Divide by zero caught!\n");
    kputs(itoa(iframe[1], 16, 32));
}*/

void c_divide_zero() {
    koops("Division by zero\n");
}

extern void c_debug() {
    kinfos("Debug exception\n");
    asm volatile("hlt");
}

extern void c_double_fault() {
    kpanic("Double fault while handling exception\n");
    hcf;
}

extern void c_generalprotection_fault() {
    kpanic("General Protection Fault\n");
}

extern void c_page_fault() {
    kpanic("Page fault\n");
}

extern void c_invalid_opcode() {
    kpanic("Invalid Opcode\n");
}

interrupt c_system_call(void *arg, unsigned long int call) {
    kputs("System called.\n");
    kputs(itoa(arg, 16, 32)); kputs("\n");
    kputs(itoa(call, 16, 32)); kputs("\n");
    
}

void idt_init() {
    idt_pointer.limit = (sizeof(idt) * 256) - 1;
    idt_pointer.base = (uint64_t)&idt_entries;
    
    //set_idt(0x0, (uint64_t)division_by_zero, 0x8E);
    set_idt(0x0, (uint64_t)divide_zero, FLAG_PRESENT | FLAG_PRIVELEGE_0 | FLAG_GATE_TYPE_TRAP);
    set_idt(0x1, (uint64_t)debug, 0x8E);
    set_idt(0x3, (uint64_t)debug, 0x8E);
    
    set_idt(0x8, (uint64_t)double_fault, FLAG_PRESENT | FLAG_PRIVELEGE_0 | FLAG_GATE_TYPE_TRAP);
    set_idt(0xD, (uint64_t)general_protection_fault, FLAG_PRESENT | FLAG_PRIVELEGE_0 | FLAG_GATE_TYPE_TRAP);
    set_idt(0xE, (uint64_t)page_fault, FLAG_PRESENT | FLAG_PRIVELEGE_0 | FLAG_GATE_TYPE_TRAP);
    set_idt(0x6, (uint64_t)invalid_opcode, FLAG_PRESENT | FLAG_PRIVELEGE_0 | FLAG_GATE_TYPE_TRAP);
    set_idt(0x7F, (uint64_t)c_system_call, FLAG_PRESENT | FLAG_PRIVELEGE_3 | FLAG_GATE_TYPE_INT);

    asm volatile("lidt %0" :: "m"(idt_pointer)); 
    //asm volatile("sti");
} 