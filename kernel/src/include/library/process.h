#pragma once
#include <stdint.h>
#include <stddef.h>

#define ATTRIBUTE_SYSTEM 0b10000000
#define ATTRIBUTE_UNKILL 0b01000000
#define ATTRIBUTE_INIT   0b11000000

#define MAX_PROCESSES 32

typedef struct {
    const char* name;
    uint8_t attributes;
    uint32_t pid;
    
    uint64_t registers[16];
    uintptr_t entry;
    uintptr_t memory_address;

} __attribute__((packed)) process;  

process create_process(const char* name, uintptr_t address, uintptr_t entry, uint8_t attributes);
void kill_process(const char* name);
void timeshare_idle();
void list_processes();