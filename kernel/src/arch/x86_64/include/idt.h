#pragma once 
#include <stdint.h>
#include <stddef.h>

#define FLAG_PRESENT        0b10000000
#define FLAG_PRIVELEGE_0    0b00000000
#define FLAG_PRIVELEGE_1    0b00100000
#define FLAG_PRIVELEGE_2    0b01000000
#define FLAG_PRIVELEGE_3    0b01100000
#define FLAG_GATE_TYPE_INT  0b00001110
#define FLAG_GATE_TYPE_TRAP 0b00001111

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed)) idt;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idtr;

void set_idt(int index, uint64_t base, uint8_t flags);

extern void double_fault();
extern void divide_zero();
extern void debug();
extern void general_protection_fault();
extern void page_fault();
extern void invalid_opcode();
//extern void system_utilities();

void idt_init();    