#pragma once
#include <stdint.h>
#include <include/string.h>
#include <include/printf.h>
#include "idt.h"

#define interrupt   __attribute__((interrupt)) extern void
#define pushall     asm("pushq %rax\n pushq %rdx\n pushq %rbx\n pushq %rsi");
#define ireturn     asm("popq %rsi\n popq %rbx\n pushq %rdx\n pushq %rax\n leave\n iretq");
#define get_stack   asm("movq %rsp, %rsi");

interrupt divide_by_zero(void*);
interrupt double_fault(void*);