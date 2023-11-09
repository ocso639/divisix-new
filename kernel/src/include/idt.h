#pragma once 
#include <stdint.h>
#include <stddef.h>

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
extern void general_protection_fault();
extern void page_fault();
extern void invalid_opcode();

void idt_init();    