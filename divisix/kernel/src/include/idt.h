#pragma once 
#include <stdint.h>
#include <stddef.h>
#define pushregs asm volatile("pushq %rax\n pushq %rdi\n pushq %rsi\n pushq %rdx\n pushq %rcx\n pushq %r8\n pushq %r9\n pushq %r10\n pushq %r11");
#define popregs asm volatile("popq %rax\n popq %rdi\n popq %rsi\n popq %rdx\n popq %rcx\n popq %r8\n popq %r9\n popq %r10\n popq %r11");
#define ireturn asm volatile("addq $8, %rsp");
#define interrupt __attribute__((interrupt)) void

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

typedef struct {
    uint64_t rax;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
} interrupt_frame;

void set_idt(int index, uint64_t base, uint8_t flags);

extern void double_fault();
extern void debug();
extern void nmi();
extern void breakpoint();
extern void overflow();
extern void boundrange();
extern void invalid_op();
extern void device_unavail();
extern void divide_zero();
 
void idt_init();    