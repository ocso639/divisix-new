#pragma once 
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint64_t gdt_null;
    uint64_t gdt_code;
    uint64_t gdt_data;
} __attribute__((packed)) gdt64;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdt64_ptr;

void init_gdt();